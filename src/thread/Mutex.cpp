#include "thread/Mutex.h"

namespace floral {
	LockGuard::LockGuard()
	{
		InitMutex(pm_Mutex);
		LockMutex(pm_Mutex);
	}

	LockGuard::~LockGuard()
	{
		UnlockMutex(pm_Mutex);
		ReleaseMutex(pm_Mutex);
	}
}
