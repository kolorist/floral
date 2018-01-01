#include "thread/windows_mutex.h"
#include "thread/mutex.h"						// api

namespace floral {

	windows_mutex::windows_mutex()
	{
		InitializeCriticalSection(&cs_handle);
	}

	windows_mutex::~windows_mutex()
	{
		DeleteCriticalSection(&cs_handle);
	}

	void windows_mutex::lock()
	{
		EnterCriticalSection(&cs_handle);
	}

	void windows_mutex::unlock()
	{
		LeaveCriticalSection(&cs_handle);
	}

}
