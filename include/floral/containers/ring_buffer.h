#pragma once

#include "floral/stdaliases.h"
#include "floral/thread/mutex.h"
#include "floral/thread/condition_variable.h"
#include "floral/assert/assert.h"

#include <atomic>

namespace floral {

#define ENABLE_MEMORY_ORDER

template <class t_type, u32 t_capacity>
class inplaced_ring_buffer_mt_spsc {
	typedef t_type								value_t;
	typedef value_t&							reference_t;
	typedef usize								index_t;

	public:
		inplaced_ring_buffer_mt_spsc()
		{
#ifdef ENABLE_MEMORY_ORDER
			m_head.store(0, std::memory_order_relaxed);
			m_tail.store(0, std::memory_order_relaxed);
#else
			m_head.store(0);
			m_tail.store(0);
#endif
		}

		void clear()
		{
			m_head.store(0, std::memory_order_relaxed);
			m_tail.store(0, std::memory_order_relaxed);
		}

		// non-block
		const bool try_pop_into(reference_t o_value)
		{
#ifdef ENABLE_MEMORY_ORDER
			const index_t currentHead = m_head.load(std::memory_order_relaxed);

			if (currentHead != m_tail.load(std::memory_order_acquire)) { // (1) synchronize with the push (2)
				o_value = m_data[currentHead % t_capacity];
				index_t nextHead = currentHead + 1;
				m_head.store(nextHead, std::memory_order_relaxed);
				return true;
			}
			return false;
#else
			const index_t currentHead = m_head.load();

			if (currentHead != m_tail.load()) {
				o_value = m_data[currentHead % t_capacity];
				index_t nextHead = currentHead + 1;
				m_head.store(nextHead);
				return true;
			}
			return false;
#endif
		}

		value_t wait_and_pop()
		{
			value_t ret;
			while(!try_pop_into(ret));
			return ret;
		}

		const bool is_empty()
		{
#ifdef ENABLE_MEMORY_ORDER
			const index_t currentHead = m_head.load(std::memory_order_relaxed);
			if (currentHead == m_tail.load(std::memory_order_relaxed))
				return true;
			return false;
#else
			const index_t currentHead = m_head.load();
			if (currentHead == m_tail.load())
				return true;
			return false;
#endif
		}

		const bool push(const t_type& i_value)
		{
#ifdef ENABLE_MEMORY_ORDER
			const index_t currentTail = m_tail.load(std::memory_order_relaxed);
			const index_t nextTail = currentTail + 1;

			if (currentTail - m_head.load(std::memory_order_relaxed) <= t_capacity - 1) {
				m_data[currentTail % t_capacity] = i_value;
				m_tail.store(nextTail, std::memory_order_release); // (2) synchronize with the pop (1)
				return true;
			}
			return false;
#else
			const index_t currentTail = m_tail.load();
			const index_t nextTail = currentTail + 1;

			if (currentTail - m_head.load() <= t_capacity - 1) {
				m_data[currentTail % t_capacity] = i_value;
				m_tail.store(nextTail);
				return true;
			}
			return false;
#endif
		}

		void wait_and_push(const t_type& i_value)
		{
			while (!push(i_value));
		}
		
		void wait_and_push(const t_type& i_value, const u32& i_loopLimit)
		{
			u32 loopCount = 0;
			while (!push(i_value))
			{
				loopCount++;
				if (loopCount > i_loopLimit)
				{
					FLORAL_CRASH;
				}
			}
		}

	private:
		value_t									m_data[t_capacity];
		std::atomic<index_t>					m_head;
		std::atomic<index_t>					m_tail;
};

template <class t_type, class t_allocator, u32 t_capacity>
class ring_buffer_st {
	public:
		ring_buffer_st()
			: m_allocator(nullptr)
		{
		}

		ring_buffer_st(t_allocator* i_allocator)
		{
			init(i_allocator);
		}

		~ring_buffer_st()
		{
			if (m_data)
				m_allocator->free(m_data);
		}

		void init(t_allocator* i_allocator)
		{
			m_allocator = i_allocator;
			m_write_slot = 0;
			m_read_slot = 0;

			m_data = m_allocator->template allocate_array<t_type>(t_capacity);
			for (sidx i = 0; i < t_capacity; i++) {
				m_data[i] = t_type();
			}
		}

		void push_back(const t_type& i_value)
		{
			sidx wslot = m_write_slot;
			sidx rslot = m_read_slot;

			m_data[wslot] = i_value;
			wslot = (wslot + 1) % (sidx)t_capacity;
			if (wslot == rslot) rslot = (rslot + 1) % (sidx)t_capacity;

			m_write_slot = wslot;
			m_read_slot = rslot;
		}

		const bool is_empty() const
		{
			return (m_write_slot == m_read_slot);
		}
		
		const bool is_full() const
		{
			return (((m_write_slot + 1) % (sidx)t_capacity) == m_read_slot);
		}

		void empty()
		{
			m_write_slot = 0;
			m_read_slot = 0;
		}

		const bool pop_front_into(t_type& o_value)
		{
			if (!is_empty()) {
				o_value = m_data[m_read_slot];
				m_read_slot = (m_read_slot + 1) % (sidx)t_capacity;
				return true;
			}
			return false;
		}

		const bool peek_front_into(t_type& o_value)
		{
			if (!is_empty()) {
				o_value = m_data[m_read_slot];
				return true;
			}
			return false;
		}

	private:
		t_allocator*						m_allocator;

		t_type*								m_data;
		
		sidx								m_write_slot;
		sidx								m_read_slot;
};

template <class t_type, class t_allocator, u32 t_size>
class ring_buffer_mt {
	typedef t_type							value_t;
	typedef value_t&						reference_t;
	typedef value_t*						pointer_t;
	typedef const value_t&					const_reference_t;
	typedef t_allocator						allocator_t;
	typedef allocator_t*					allocator_ptr_t;
	typedef u32								index_t;

	public:
		ring_buffer_mt()
			: m_allocator(nullptr)
		{ }

		ring_buffer_mt(allocator_ptr_t i_allocator)
		{
			assign_allocator(i_allocator);
		}

		void assign_allocator(allocator_ptr_t i_allocator)
		{
			m_allocator = i_allocator;
			m_data = m_allocator->template allocate_array<value_t>(t_size);
			m_head = 0; m_tail = 0;			// head == tail => buffer empty
		}

		// non-block
		const bool try_pop_into(reference_t o_value)
		{
			return pop_head_into(o_value);
		}

		value_t wait_and_pop()
		{
			while (get_head() == get_tail()) {
				m_data_condvar.wait(m_data_condvar_mtx);
			}

			value_t retData = m_data[m_head];
			m_head = (m_head + 1) % t_size;
			return retData;
		}

		void push(const_reference_t i_value)
		{
			m_head_mtx.lock();
			m_tail_mtx.lock();
			index_t newTail = (m_tail + 1) % t_size;
			FLORAL_ASSERT_MSG(newTail != m_head, "Ring buffer was overrun! Please increase the buffer size.");
			m_head_mtx.unlock();
			m_data[m_tail] = i_value;
			m_tail = newTail;
			m_tail_mtx.unlock();
			m_data_condvar.notify_one();
		}

		const bool is_empty() const {
			lock_guard headGuard(m_head_mtx);
			if (m_head == get_tail())
				return true;
			else return false;
		}

	private:
		const index_t get_head() {
			lock_guard headGuard(m_head_mtx);
			return m_head;
		}

		const index_t get_tail() {
			lock_guard tailGuard(m_tail_mtx);
			return m_tail;
		}

		const bool pop_head_into(reference_t o_value)
		{
			lock_guard headGuard(m_head_mtx);
			if (m_head == get_tail())
				return false;

			o_value = m_data[m_head];
			m_head = (m_head + 1) % t_size;
			return true;
		}

	private:
		pointer_t							m_data;
		allocator_ptr_t						m_allocator;
		index_t								m_head;
		index_t								m_tail;

		mutex								m_head_mtx;
		mutex								m_tail_mtx;
		mutex								m_data_condvar_mtx;
		condition_variable					m_data_condvar;
};
}
