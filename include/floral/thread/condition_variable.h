#pragma once

#include "floral/stdaliases.h"

#if defined(FLORAL_PLATFORM_WINDOWS)
#include "windows_condition_variable.h"
#elif defined (FLORAL_PLATFORM_POSIX)
#include "posix_condition_variable.h"
#endif

namespace floral {

#if defined(FLORAL_PLATFORM_WINDOWS)
	typedef windows_condition_variable			condition_variable;
#elif defined(FLORAL_PLATFORM_POSIX)
	typedef posix_condition_variable			condition_variable;
#endif

	typedef condition_variable*					condition_variable_ptr_t;
	typedef condition_variable&					condition_variable_ref_t;

}