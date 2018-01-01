#ifndef __FLORAL_THREAD_BASE_H__
#define __FLORAL_THREAD_BASE_H__

#include <stdaliases.h>

namespace floral {
	typedef void								(*thread_func_t)(voidptr pData);

	struct thread_base {
		thread_func_t							entry_point;
		voidptr									ptr_data;

		thread_base()
			: entry_point(nullptr)
			, ptr_data(nullptr)
		{ }
	};
}

#endif // __FLORAL_THREAD_BASE_H__
