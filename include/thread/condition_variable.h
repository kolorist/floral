#ifndef __FLORAL_CONDITION_VARIABLE_H__
#define __FLORAL_CONDITION_VARIABLE_H__

#include <stdaliases.h>

#if defined(PLATFORM_WINDOWS)
#include "windows_condition_variable.h"
#elif defined (PLATFORM_POSIX)
#include "posix_condition_variable.h"
#endif

namespace floral {

#if defined(PLATFORM_WINDOWS)
	typedef windows_condition_variable			condition_variable;
#elif defined(PLATFORM_POSIX)
	typedef posix_condition_variable			condition_variable;
#endif

	typedef condition_variable*					condition_variable_ptr_t;
	typedef condition_variable&					condition_variable_ref_t;

}

#endif // __FLORAL_CONDITION_VARIABLE_H__
