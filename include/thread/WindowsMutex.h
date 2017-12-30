#ifndef __FLORAL_WIN32_MUTEX_H__
#define __FLORAL_WIN32_MUTEX_H__

#include <stdaliases.h>

#include <Windows.h>

namespace floral {
	struct WindowsMutex {
		CRITICAL_SECTION						pm_Handle;
	};
}

#endif // __FLORAL_WIN32_MUTEX_H__
