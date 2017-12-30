#ifndef __FLORAL_WINDOWS_THREAD_H__
#define __FLORAL_WINDOWS_THREAD_H__

#include <stdaliases.h>

#include <Windows.h>

#include "ThreadBase.h"

namespace floral {
	struct WindowsThread : ThreadBase {
		DWORD									Id;
		HANDLE									Handle;
	};
}

#endif // __FLORAL_WINDOWS_THREAD_H__
