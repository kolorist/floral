#ifndef __FLORAL_MUTEX_H__
#define __FLORAL_MUTEX_H__

#include <stdaliases.h>

#if defined(PLATFORM_WINDOWS)
#include "WindowsMutex.h"
#elif defined(PLATFORM_POSIX)
#include "PosixMutex.h"
#endif

namespace floral {

#if defined(PLATFORM_WINDOWS)
	typedef WindowsMutex						Mutex;
#elif defined(PLATFORM_POSIX)
	typedef PosixMutex							Mutex;
#endif

	struct LockGuard {
		LockGuard();
		~LockGuard();
		Mutex									pm_Mutex;
	};

	typedef Mutex*								MutexPtr;
	typedef Mutex&								MutexRef;

	////////////////////////////////////////////
	void										InitMutex(MutexRef mtx);
	void										LockMutex(MutexRef mtx);
	void										UnlockMutex(MutexRef mtx);
	void										ReleaseMutex(MutexRef mtx);
	////////////////////////////////////////////
}

#endif // __FLORAL_MUTEX_H__
