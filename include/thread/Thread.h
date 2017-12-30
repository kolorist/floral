#ifndef __FLORAL_THREAD_H__
#define __FLORAL_THREAD_H__

#include <stdaliases.h>

#include "ThreadBase.h"
#if defined(PLATFORM_WINDOWS)
#include "WindowsThread.h"
#elif defined(PLATFORM_POSIX)
#include "PosixThread.h"
#endif

namespace floral {

#if defined(PLATFORM_WINDOWS)
	typedef WindowsThread						Thread;
#elif defined(PLATFORM_POSIX)
	typedef PosixThread							Thread;
#endif

	typedef Thread*								ThreadPtr;
	typedef Thread&								ThreadRef;

	////////////////////////////////////////////
	void										InitThread(ThreadRef rThread);
	void										StartThread(ThreadRef pThread);
	void										WaitForThread(ThreadRef rThread);
	void										ReleaseThread(ThreadRef rThread);
	////////////////////////////////////////////

}

#endif // __FLORAL_THREAD_H__
