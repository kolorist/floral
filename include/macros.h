#ifndef __FLORAL_MACROS_H__
#define __FLORAL_MACROS_H__

////////////////////////////////////////////////

#define DECLARE_STATIC_CONSTANT(type, expression) \
	enum { \
		expression \
	}
//#define DECLARE_STATIC_CONSTANT(type, expression) \
	//static const type expression;

////////////////////////////////////////////////

#endif // __FLORAL_MACROS_H__
