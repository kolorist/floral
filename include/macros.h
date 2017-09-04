#ifndef __FLORAL_MACROS_H__
#define __FLORAL_MACROS_H__

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

#endif // __FLORAL_MACROS_H__
