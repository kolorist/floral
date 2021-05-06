#ifndef __FLORAL_WINDOWS_THREAD_H__
#define __FLORAL_WINDOWS_THREAD_H__

#include "floral/stdaliases.h"

#include "thread_base.h"

#include <Windows.h>

namespace floral {
	struct windows_thread : thread_base {
		DWORD									id;
		HANDLE									thread_handle;

		windows_thread();
		~windows_thread();

		void start();
	};

	////////////////////////////////////////////
	const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // Must be 0x1000.
		LPCSTR szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)
}

#endif // __FLORAL_WINDOWS_THREAD_H__
