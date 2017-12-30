#include "thread/WindowsConditionVariable.h"
#include "thread/ConditionVariable.h"			// api

namespace floral {
#define EVENT_NOTIFY_ONE						0
#define EVENT_NOTIFY_ALL						1

	void InitConditionVariable(ConditionVariableRef condVar)
	{
		condVar.pm_WaitersCount = 0;
		condVar.pm_NotifyEvents[EVENT_NOTIFY_ONE] = CreateEvent(NULL, FALSE, FALSE, NULL);
		condVar.pm_NotifyEvents[EVENT_NOTIFY_ALL] = CreateEvent(NULL, TRUE, FALSE, NULL);
		InitializeCriticalSection(&condVar.pm_WaitersCountLock);
	}

	void WaitForCondition(ConditionVariableRef condVar, MutexRef mtx)
	{
		EnterCriticalSection(&condVar.pm_WaitersCountLock);
		condVar.pm_WaitersCount++;
		LeaveCriticalSection(&condVar.pm_WaitersCountLock);

		UnlockMutex(mtx);
		// wait
		s32 result = WaitForMultipleObjects(2, condVar.pm_NotifyEvents, FALSE, INFINITE);
		EnterCriticalSection(&condVar.pm_WaitersCountLock);
		condVar.pm_WaitersCount--;
		bool isLastWaiter = (result == (WAIT_OBJECT_0 + EVENT_NOTIFY_ALL)) && (condVar.pm_WaitersCount == 0);
		LeaveCriticalSection(&condVar.pm_WaitersCountLock);
		if (isLastWaiter)
			ResetEvent(condVar.pm_NotifyEvents[EVENT_NOTIFY_ALL]);
		// end waiting
		LockMutex(mtx);
	}

	void NotifyOneWaiter(ConditionVariableRef condVar)
	{
		EnterCriticalSection(&condVar.pm_WaitersCountLock);
		bool isHaveWaiters = (condVar.pm_WaitersCount > 0);
		LeaveCriticalSection(&condVar.pm_WaitersCountLock);
		if (isHaveWaiters)
			SetEvent(condVar.pm_NotifyEvents[EVENT_NOTIFY_ONE]);
	}

	void NotifyAllWaiters(ConditionVariableRef condVar)
	{
		EnterCriticalSection(&condVar.pm_WaitersCountLock);
		bool isHaveWaiters = (condVar.pm_WaitersCount > 0);
		LeaveCriticalSection(&condVar.pm_WaitersCountLock);
		if (isHaveWaiters)
			SetEvent(condVar.pm_NotifyEvents[EVENT_NOTIFY_ALL]);
	}

	void ReleaseConditionVariable(ConditionVariableRef condVar)
	{
		CloseHandle(condVar.pm_NotifyEvents[EVENT_NOTIFY_ONE]);
		CloseHandle(condVar.pm_NotifyEvents[EVENT_NOTIFY_ALL]);
		DeleteCriticalSection(&condVar.pm_WaitersCountLock);
	}
}
