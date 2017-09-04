#ifndef __FLORAL_ASSERTIONS_H__
#define __FLORAL_ASSERTIONS_H__

////////////////////////////////////////////////
#if defined(FLORAL_UNIT_TEST)
#	define ASSERT(expression)					if (!(expression)) throw "An error occured!"
#	define ASSERT_MSG(expression, msg)			if (!(expression)) throw msg
#else
#	include <cassert>
#	define ASSERT(expression)					assert(expression)
#	define ASSERT_MSG(expression, msg)			assert(expression && msg)
#endif

#endif // __FLORAL_ASSERTIONS_H__