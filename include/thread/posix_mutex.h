#pragma once

#include <stdaliases.h>

#include <pthread.h>

namespace floral {
	struct posix_mutex {
		pthread_mutex_t							cs_handle;

		posix_mutex();
		~posix_mutex();

		void lock();
		void unlock();
	};
}
