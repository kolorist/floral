#include "thread/windows_thread.h"
#include "thread/thread.h"						// api

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
	////////////////////////////////////////////
}
