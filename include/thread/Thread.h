#ifndef __FLORAL_THREAD_H__
#define __FLORAL_THREAD_H__

#include <stdaliases.h>

#include "thread_base.h"
#if defined(PLATFORM_WINDOWS)
#include "windows_thread.h"
#elif defined(PLATFORM_POSIX)
#include "posix_thread.h"
#endif

namespace floral {

#if defined(PLATFORM_WINDOWS)
	typedef windows_thread						thread;
#elif defined(PLATFORM_POSIX)
	typedef posix_thread						thread;
#endif

	typedef thread*								thread_ptr_t;
	typedef thread&								thread_ref_t;

	////////////////////////////////////////////
	void										wait_for_thread(thread_ref_t rThread);
	////////////////////////////////////////////

}

#endif // __FLORAL_THREAD_H__
