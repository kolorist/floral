#include "floral/thread/windows_thread.h"
#include "floral/thread/thread.h"

namespace floral {

	DWORD WINAPI windows_thread_func(LPVOID lpParam)
	{
		thread_ptr_t myThread = (thread_ptr_t)lpParam;
		(*myThread->entry_point)(myThread->ptr_data);
		return 0;
	}

	windows_thread::windows_thread()
		: thread_base()
		, id(0)
		, thread_handle(NULL)
	{ }

	windows_thread::~windows_thread()
	{
		// nothing for now
	}

	void windows_thread::start()
	{
		thread_handle = CreateThread(
				NULL,
				0,
				windows_thread_func,
				this,
				0,
				&id);
	}

	////////////////////////////////////////////
	void wait_for_thread(thread_ref_t rThread)
	{
		WaitForSingleObject(rThread.thread_handle, INFINITE);
	}

	void set_current_thread_name(const_cstr name)
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = name;
		info.dwThreadID = -1;					// -1 means calling thread
		info.dwFlags = 0;

		__try
		{
			RaiseException(MS_VC_EXCEPTION,
					0,
					sizeof(info)/sizeof(ULONG_PTR),
					(ULONG_PTR*)&info);
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
		}
	}
	////////////////////////////////////////////
}
