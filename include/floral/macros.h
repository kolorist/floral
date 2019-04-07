#pragma once

////////////////////////////////////////////////

#define DECLARE_STATIC_CONSTANT(type, expression) \
	enum { \
		expression \
	}
//#define DECLARE_STATIC_CONSTANT(type, expression) \
	//static const type expression;

////////////////////////////////////////////////
