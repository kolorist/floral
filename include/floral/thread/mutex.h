#pragma once

#include "floral/stdaliases.h"

#if defined(FLORAL_PLATFORM_WINDOWS)
#include "windows_mutex.h"
#elif defined(FLORAL_PLATFORM_POSIX)
#include "posix_mutex.h"
#endif

namespace floral {

#if defined(FLORAL_PLATFORM_WINDOWS)
	typedef windows_mutex						mutex;
#elif defined(FLORAL_PLATFORM_POSIX)
	typedef posix_mutex							mutex;
#endif

	typedef mutex*								mutex_ptr_t;
	typedef mutex&								mutex_ref_t;

	struct lock_guard {
		lock_guard(mutex_ref_t mtx);
		~lock_guard();

		mutex_ref_t								ref_mutex;
	};

}