#include "thread/windows_condition_variable.h"
#include "thread/condition_variable.h"			// api

namespace floral {

#define EVENT_NOTIFY_ONE						0
#define EVENT_NOTIFY_ALL						1

	windows_condition_variable::windows_condition_variable()
		: waiters_count(0)
	{
		notify_events[EVENT_NOTIFY_ONE] = CreateEvent(NULL, FALSE, FALSE, NULL);
		notify_events[EVENT_NOTIFY_ALL] = CreateEvent(NULL, TRUE, FALSE, NULL);
		InitializeCriticalSection(&waiters_count_lock);
	}

	windows_condition_variable::~windows_condition_variable()
	{
		CloseHandle(notify_events[EVENT_NOTIFY_ONE]);
		CloseHandle(notify_events[EVENT_NOTIFY_ALL]);
		DeleteCriticalSection(&waiters_count_lock);
	}

	void windows_condition_variable::wait(mutex_ref_t mtx)
	{
		EnterCriticalSection(&waiters_count_lock);
		waiters_count++;
		LeaveCriticalSection(&waiters_count_lock);

		mtx.unlock();
		// wait
		s32 result = WaitForMultipleObjects(2, notify_events, FALSE, INFINITE);
		EnterCriticalSection(&waiters_count_lock);
		waiters_count--;
		bool isLastWaiter = (result == (WAIT_OBJECT_0 + EVENT_NOTIFY_ALL)) && (waiters_count == 0);
		LeaveCriticalSection(&waiters_count_lock);
		if (isLastWaiter)
			ResetEvent(notify_events[EVENT_NOTIFY_ALL]);
		// end waiting
		mtx.lock();
	}

	void windows_condition_variable::notify_one()
	{
		EnterCriticalSection(&waiters_count_lock);
		bool isHaveWaiters = (waiters_count > 0);
		LeaveCriticalSection(&waiters_count_lock);
		if (isHaveWaiters)
			SetEvent(notify_events[EVENT_NOTIFY_ONE]);
	}

	void windows_condition_variable::notify_all()
	{
		EnterCriticalSection(&waiters_count_lock);
		bool isHaveWaiters = (waiters_count > 0);
		LeaveCriticalSection(&waiters_count_lock);
		if (isHaveWaiters)
			SetEvent(notify_events[EVENT_NOTIFY_ALL]);
	}
}
