#pragma once

#include "floral/stdaliases.h"

#include "thread_base.h"

#include <pthread.h>

namespace floral {
	struct posix_thread : thread_base {

		pthread_t								thread_handle;

		posix_thread();
		~posix_thread();

		void start();
	};
}
