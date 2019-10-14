#pragma once

/***********************************************
Ok! Before implementing this type_list structure, let's ask ourself a question:
Why do we need type_list?
> The main reason as I can see it myself now is:
	C++ does not support variable number of template parameter
B-But there is variadic template mechanism, can we use it? :(
> Unfortunately, we can only use it in declaration, we can't use it
	when implementing functions.
N-No way :( there is also function recursion to the rescue, right?
> Then go do it yourself, fuckers -.-
************************************************/

#include "floral/macros.h"

#include "atomic_types.h"

template <class _head_elem, class _tail_list>
struct type_list {
	using head_elem = _head_elem;
	using tail_list = _tail_list;
};

// type_list length
template <typename> struct tl_length;

template <>
struct tl_length<null_type> {
	//DECLARE_STATIC_CONSTANT(unsigned int, value = 0u);
	enum {
		value = 0u
	};
};

template <class _head_elem, typename _tail_list>
struct tl_length<type_list<_head_elem, _tail_list> > {
	//DECLARE_STATIC_CONSTANT(unsigned int, value = 1u + tl_length<_tail_list>::value);
	enum {
		value = 1u + tl_length<_tail_list>::value
	};
};

// type_list index access
//TODO: static_assert for int, it must be unsigned int
template <int, typename> struct tl_type_at;

template <int _idx>
struct tl_type_at<_idx, null_type> {
    typedef null_type                           type;
};

template <class _head_elem, typename _tail_list>
struct tl_type_at<0, type_list<_head_elem, _tail_list> > {
    typedef _head_elem                          type;
};

template <int _idx, class _head_elem, typename _tail_list> 
struct tl_type_at<_idx, type_list<_head_elem, _tail_list> > {
    typedef typename tl_type_at<_idx - 1, _tail_list>::type     type;
};

template <int _idx, class _type_list>
using tl_type_at_t = typename tl_type_at<_idx, _type_list>::type;

// type_list index access with fallback type
template <int, typename, typename> struct tl_fb_type_at;

template <int _idx, typename _fallback_type>
struct tl_fb_type_at<_idx, null_type, _fallback_type> {
	typedef _fallback_type						type;
};

template <class _head_elem, typename _tail_list, typename _fallback_type>
struct tl_fb_type_at<0, type_list<_head_elem, _tail_list>, _fallback_type> {
    typedef _head_elem                          type;
};

template <int _idx, class _head_elem, typename _tail_list, typename _fallback_type> 
struct tl_fb_type_at<_idx, type_list<_head_elem, _tail_list>, _fallback_type> {
    typedef typename tl_fb_type_at<_idx - 1, _tail_list, _fallback_type>::type     type;
};

template <int _idx, class _type_list, typename _fallback_type>
using tl_fb_type_at_t = typename tl_fb_type_at<_idx, _type_list, _fallback_type>::type;

// type_list declaration helpers
#define type_list_1(t1)							type_list<t1, null_type>
#define type_list_2(t1, t2)						type_list<t1, type_list_1(t2)>
#define type_list_3(t1, t2, t3)					type_list<t1, type_list_2(t2, t3)>
#define type_list_4(t1, t2, t3, t4)				type_list<t1, type_list_3(t2, t3, t4)>
#define type_list_5(t1, t2, t3, t4, t5)			type_list<t1, type_list_4(t2, t3, t4, t5)>