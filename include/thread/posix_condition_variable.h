#pragma once

#include <stdaliases.h>

#include <pthread.h>

namespace floral {
	struct posix_condition_variable {
		pthread_cond_t							cond_var;
		
		posix_condition_variable();
		~posix_condition_variable();

		void wait(mutex_ref_t i_mtx);
		void notify_one();
		void notify_all();
	};
}
