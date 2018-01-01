#include "thread/Mutex.h"

namespace floral {
	lock_guard::lock_guard(mutex_ref_t mtx)
		: ref_mutex(mtx)
	{
		ref_mutex.lock();
	}

	lock_guard::~lock_guard()
	{
		ref_mutex.unlock();
	}
}
