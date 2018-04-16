#ifndef __FLORAL_QUEUE_H__
#define __FLORAL_QUEUE_H__

#include <stdaliases.h>

#include <thread/mutex.h>
#include <thread/condition_variable.h>

namespace floral {

	// TODO: t_type need to be assignable, how does other implementation deal with this?
	template <class t_type>
	struct queue_node {
		t_type									data;
		queue_node*								next;

		queue_node()
			: next(nullptr)
		{ }
	};

	template <class t_type, class t_allocator>
	class queue_mt_lockbased {
		typedef t_type							value_type;
		typedef value_type*						pointer_type;
		typedef value_type&						reference_type;
		typedef const value_type&				const_reference_type;
		typedef t_allocator						allocator_type;
		typedef allocator_type*					allocator_ptr_type;

		typedef queue_node<value_type>*			queue_node_ptr;

		// sentinel_node contains nothing and cannot be a constant because we need its address as non-const
		static queue_node<value_type>			sentinel_node;

		public:
			queue_mt_lockbased()
				: my_allocator(nullptr)
			{ }
		
			queue_mt_lockbased(allocator_ptr_type myAllocator)
			{
				assign_allocator(myAllocator);
			}
			
			void assign_allocator(allocator_ptr_type myAllocator)
			{
				my_allocator = myAllocator;
				// TODO: assert for my_allocator
				head_node = my_allocator->allocate<queue_node<value_type>>();
				tail_node = head_node;			// tail == head means the queue is empty
			}

			value_type try_pop() {
				queue_node_ptr oldHead = pop_head();
				if (oldHead) {
					value_type retData = oldHead->data;
					my_allocator->free(oldHead);
					return retData;
				}
				// TODO: if value_type is a pointer type, will this be nullptr?
				return value_type();
			}

			value_type wait_and_pop() {
				head_mtx.lock();
				while (head_node == get_tail()) {
					data_condvar.wait(data_condvar_mtx);
				}
				queue_node_ptr oldHead = head_node;
				head_node = head_node->next;
				head_mtx.unlock();

				value_type retData = oldHead->data;
				my_allocator->free(oldHead);
				return retData;
			}

			void push(const_reference_type val) {
				queue_node_ptr newTail = my_allocator->allocate<queue_node<value_type>>();
				tail_mtx.lock();
				tail_node->data = val;
				tail_node->next = newTail;
				tail_node = newTail;
				tail_mtx.unlock();
				data_condvar.notify_one();
			}

			const bool is_empty() const {
				lock_guard headGuard(head_mtx);
				if (head_node == get_tail())
					return true;
				else return false;
			}

		private:
			/*
			 * Why we have to lock the tail / head when perform reading?
			 *	> By locking, we prevent any threads from modify the current value of head / tail
			 *		>> The value we read always is the right element of the queue
			 *		>>> If we dont have this lock, other thread can call Push() while we GetTail()
			 *			which result in an undefined behavior (cuz the m_Tail's data may be not-completed)
			 */
			queue_node_ptr get_tail() {
				lock_guard tailGuard(tail_mtx);
				return tail_node;
			}

			/*
			 * Why the following commented implementation is broken?
			 *	> It's broken when 2 threads call TryPop() concurrently
			 *		>> Consider queue has only 1 element for simplicity
			 *		>> Thread 1 get the currTail, attempt to lock the head but Thread 2 lock it first
			 *			Thread 2 complete it operation -> m_Tail move backward, now the queue is empty
			 *			Thread 1 acquire the lock, compare the Head with currTail (which is now a wild pointer),
			 *				and it will pass the compare, the Head will now be popped out, move to the next pointer of it
			 *		>>> The queue is now corrupted.
			 *	> By locking the Head Mutex first, we prevent other threads from execute PopHead() concurrently with us
			 *		and we are safe.
			 */
			queue_node_ptr pop_head() {
				// broken implementation:
				// pointer_type currTail = GetTail();
				// tthread::lock_guard<tthread::mutex> headGuard(m_HeadMutex);
				// if (m_Head = currTail) {
				//	 return nullptr;
				// }
				lock_guard headGuard(head_mtx);
				if (head_node == get_tail()) {
					return nullptr;
				}

				queue_node_ptr oldHead = head_node;
				head_node = head_node->next;
				return oldHead;
			}

		private:
			mutex								head_mtx;
			mutex								tail_mtx;
			mutex								data_condvar_mtx;
			condition_variable					data_condvar;

			queue_node_ptr						head_node;
			queue_node_ptr						tail_node;

			allocator_ptr_type					my_allocator;
	};
}

#include "queue.hpp"

#endif // __FLORAL_QUEUE_H__
