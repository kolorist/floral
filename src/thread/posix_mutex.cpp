#include "floral/thread/posix_mutex.h"
#include "floral/thread/mutex.h"

namespace floral {
	posix_mutex::posix_mutex()
	{
		pthread_mutex_init(&cs_handle, nullptr);
	}

	posix_mutex::~posix_mutex()
	{
		pthread_mutex_destroy(&cs_handle);
	}

	void posix_mutex::lock()
	{
		pthread_mutex_lock(&cs_handle);
	}
	
	void posix_mutex::unlock()
	{
		pthread_mutex_unlock(&cs_handle);
	}
}
