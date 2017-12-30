#include "thread/WindowsMutex.h"
#include "thread/Mutex.h"						// api

namespace floral {
	void InitMutex(MutexRef mtx)
	{
		InitializeCriticalSection(&mtx.pm_Handle);
	}

	void LockMutex(MutexRef mtx)
	{
		EnterCriticalSection(&mtx.pm_Handle);
	}

	void UnlockMutex(MutexRef mtx)
	{
		LeaveCriticalSection(&mtx.pm_Handle);
	}

	void ReleaseMutex(MutexRef mtx)
	{
		DeleteCriticalSection(&mtx.pm_Handle);
	}
}
