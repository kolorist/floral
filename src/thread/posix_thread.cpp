#include "floral/thread/posix_thread.h"
#include "floral/thread/thread.h"

namespace floral {
	voidptr posix_thread_func(voidptr param)
	{
		thread_ptr_t myThread = (thread_ptr_t)param;
		(*myThread->entry_point)(myThread->ptr_data);
		pthread_exit(nullptr);
	}

	posix_thread::posix_thread()
		: thread_base()
	{
	}

	posix_thread::~posix_thread()
	{
		// nothing for now
	}

	void posix_thread::start()
	{
		pthread_create(&thread_handle, nullptr, posix_thread_func, this);
	}

	// -----------------------------------------
	void wait_for_thread(thread_ref_t i_thread)
	{
		pthread_join(i_thread.thread_handle, nullptr);
	}

	void set_current_thread_name(const_cstr i_name)
	{
		pthread_setname_np(pthread_self(), i_name);
	}
}
