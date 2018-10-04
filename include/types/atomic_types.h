#ifndef __ATOMIC_TYPES_H__
#define __ATOMIC_TYPES_H__

#include "macros.h"

class null_type {};

// intergral_constant
template <class _type, _type _value>
struct intergral_constant {
/************************************************
Q: What? enum? Why don't you use 'static const', it's more clearly that way!
 Short answer: 'enum' is just like a literal constanst.
 Long answer:
	When passing be reference, with 'static const', there will be template instantiating
	(this is done in run-time so it will break our pure compile-time calculation).
	ref: https://lists.boost.org/Archives/boost/2003/01/41847.php
************************************************/
	//DECLARE_STATIC_CONSTANT(_type, value = _value);
	enum {
		value = _value
	};
};

// true_false_types
using true_type = intergral_constant<bool, true>;
//typedef intergral_constant<bool, true>			true_type;
using false_type = intergral_constant<bool, false>;
//typedef intergral_constant<bool, false>			false_type;
/***********************************************
Oh! Hold on!
Q: Can we use 'typedef' here instead of the 'using' keyword?
 Short answer: 'using' keyword is cooler xD.
 Long answer:
	Normally, they are equivalent.

	'typedef' cannot do this:

	// my_type is a typedef
	my_type<T> my_var;

	while 'using' can, if we really hate 'using' there is a way to do it by using 'typedef'
	(That's why you usually see a 'rebind' struct inside C++ STL)

	please refer to: http://stackoverflow.com/questions/10747810/what-is-the-difference-between-typedef-and-using-in-c11
************************************************/

#endif // __ATOMIC_TYPES_H__
