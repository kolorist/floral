#pragma once

#include "floral/stdaliases.h"
#include "floral/thread/mutex.h"

#include "queue.h"

namespace floral
{

template <class t_type, size t_capacity>
class inplace_spsc_double_queue_lock_based_t
{
	typedef t_type								value_t;
	typedef value_t&							reference_t;

public:
	typedef inplace_queue_t<t_type, t_capacity>	queue_t;

public:
	inplace_spsc_double_queue_lock_based_t()
		: m_composing_queue_idx(0)
	{
	}

	void push(const t_type& i_value)
	{
		lock_guard guard(m_data_mtx);

		m_queues[m_composing_queue_idx].push(i_value);
	}

	queue_t& flip()
	{
		lock_guard guard(m_data_mtx);
		queue_t& retQueue = m_queues[m_composing_queue_idx];

		m_composing_queue_idx = (m_composing_queue_idx + 1) % 2;
		m_queues[m_composing_queue_idx].reset();

		return retQueue;
	}

private:
	queue_t										m_queues[2];
	size										m_composing_queue_idx;
	mutex										m_data_mtx;
};

}
