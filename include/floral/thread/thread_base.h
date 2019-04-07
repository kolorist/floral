#pragma once

#include "floral/stdaliases.h"

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