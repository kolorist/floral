#pragma once

#include "stdaliases.h"

#include "thread/mutex.h"
#include "thread/condition_variable.h"

#include "assert/assert.h"

namespace floral {

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
