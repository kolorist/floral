#ifndef __COMMONS_H__
#define __COMMONS_H__

////////////////////////////////////////////////
#if defined(FLORAL_UNIT_TEST)
#	define ASSERT(expression)					if (!(expression)) throw "An error occured!"
#	define ASSERT_MSG(expression, msg)			if (!(expression)) throw msg
#else
#	include <cassert>
#	define ASSERT(expression)					assert(expression)
#	define ASSERT_MSG(expression, msg)			assert(expression && msg)
#endif

////////////////////////////////////////////////

#define USE_ENUM_FOR_STATIC_CONSTANTS

#if defined(USE_ENUM_FOR_STATIC_CONSTANTS)
#define DECLARE_STATIC_CONSTANT(type, expression) \
	enum { \
		expression \
	}
#else
#define DECLARE_STATIC_CONSTANT(type, expression) \
	static const type expression;
#endif

////////////////////////////////////////////////

#endif // __COMMONS_H__
