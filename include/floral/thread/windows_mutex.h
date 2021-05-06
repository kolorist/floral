#ifndef __FLORAL_WINDOWS_MUTEX_H__
#define __FLORAL_WINDOWS_MUTEX_H__

#include "floral/stdaliases.h"

#include <Windows.h>

namespace floral {
	struct windows_mutex {
		CRITICAL_SECTION						cs_handle;

		windows_mutex();
		~windows_mutex();

		void lock();
		void unlock();
	};
}

#endif // __FLORAL_WINDOWS_MUTEX_H__
