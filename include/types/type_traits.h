#ifndef __FLORAL_TYPE_TRAITS_H__
#define __FLORAL_TYPE_TRAITS_H__

/***********************************************
Traits are a generic programming technique which allows we to make compile-time decisions
that depend on *data types*

It is similar to run-time decision making we are all used to perform using *values* of *data types*

Example: copying an int value VS copying a c-string (char*) -> can be decided at compile-time
***********************************************/

#include "macros.h"
#include "atomic_types.h"

template <class _type>
class type_traits {
private:

// pointer_traits
	// generic template implementation
	template <class>							// C++'s motto: we doesn't have to name it while we won't use it
	struct pointer_traits : false_type {
		// default: all is non-pointer
		typedef null_type						type;
	};

	// specific template implementation
	template <class __type>
	struct pointer_traits<__type*> : true_type {
		typedef __type							type;
	};

// member_pointer_traits


public:
	//DECLARE_STATIC_CONSTANT(bool, is_pointer = pointer_traits<_type>::value);
	enum {
		is_pointer = pointer_traits<_type>::value
	};
	// have 'typename' keyword due to 'type' is a dependent-type (depends on _type)
	typedef typename pointer_traits<_type>::type			pointee_type;

};

// pointer_type_manipulators
template <class _type>
struct to_pointer {
	typedef _type*								type;
};

template <class _type>
struct to_pointer<_type*> {
	typedef _type*								type;
};

template <class _type>
using to_pointer_t = typename to_pointer<_type>::type;

#endif // __FLORAL_TYPE_TRAITS_H__
