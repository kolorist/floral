#pragma once

#include "floral/stdaliases.h"

#include "thread_base.h"
#if defined(FLORAL_PLATFORM_WINDOWS)
#include "windows_thread.h"
#elif defined(PLATFORM_POSIX)
#include "posix_thread.h"
#endif

namespace floral {

#if defined(FLORAL_PLATFORM_WINDOWS)
	typedef windows_thread						thread;
#elif defined(PLATFORM_POSIX)
	typedef posix_thread						thread;
#endif

	typedef thread*								thread_ptr_t;
	typedef thread&								thread_ref_t;

	////////////////////////////////////////////
	void										wait_for_thread(thread_ref_t rThread);
	void										set_current_thread_name(const_cstr name);
	////////////////////////////////////////////

}