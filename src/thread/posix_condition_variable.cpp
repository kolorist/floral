#include "thread/posix_condition_variable.h"

#include "thread/posix_mutex.h"

namespace floral {
	posix_condition_variable::posix_condition_variable()
	{
		pthread_cond_init(&cond_var, nullptr);
	}

	posix_condition_variable::~posix_condition_variable()
	{
		pthread_cond_destroy(&cond_var);
	}

	void posix_condition_variable::wait(mutex_ref_t i_mtx)
	{
		pthread_cond_wait(&cond_var, &i_mtx.cs_handle);
	}
	
	void posix_condition_variable::notify_one()
	{
		pthread_cond_signal(&cond_var);
	}

	void posix_condition_variable::notify_all()
	{
		pthread_cond_broadcast(&cond_var);
	}
}
