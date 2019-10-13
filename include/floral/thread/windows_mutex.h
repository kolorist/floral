#ifndef __FLORAL_WINDOWS_MUTEX_H__
#define __FLORAL_WINDOWS_MUTEX_H__

#include "floral/stdaliases.h"

#define WIN32_LEAN_AND_MEAN
// NOTE: we have to define NOMINMAX when including Windows.h because the min(), max()
// function of Windows API may conflict with floral::min() and floral::max()
#define NOMINMAX
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
