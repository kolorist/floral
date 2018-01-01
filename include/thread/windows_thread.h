#ifndef __FLORAL_WINDOWS_THREAD_H__
#define __FLORAL_WINDOWS_THREAD_H__

#include <stdaliases.h>

#define WIN32_LEAN_AND_MEAN
// NOTE: we have to define NOMINMAX when including Windows.h because the min(), max()
// function of Windows API may conflict with floral::min() and floral::max()
#define NOMINMAX
#include <Windows.h>

#include "thread_base.h"

namespace floral {
	struct windows_thread : thread_base {
		DWORD									id;
		HANDLE									thread_handle;

		windows_thread();
		~windows_thread();

		void start();
	};
}

#endif // __FLORAL_WINDOWS_THREAD_H__
