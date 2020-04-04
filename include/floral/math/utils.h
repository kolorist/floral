#pragma once

#include "floral/stdaliases.h"

namespace floral {

constexpr f32 pi = 3.1415926525898f;
constexpr f32 half_pi = 1.5707963267948966f;
#ifndef PI
#define PI										3.1415926525898f
#endif

#ifndef TEST_BIT
#define		TEST_BIT(target, bitmask)			(target & bitmask)
#endif
#ifndef TEST_BIT_BOOL
#define		TEST_BIT_BOOL(target, bitmask)		((target & bitmask) != 0)
#endif
#ifndef SET_BIT
#define		SET_BIT(target, bitmask)			(target = target | bitmask)
#endif
#ifndef CLEAR_BIT
#define		CLEAR_BIT(target, bitmask)			(target = target & (~bitmask))
#endif

template <class DType>
DType min(DType lhs, DType rhs) {
	return (lhs > rhs ? rhs : lhs);
}

template <class DType>
DType max(DType lhs, DType rhs) {
	return (lhs > rhs ? lhs : rhs);
}

template <class DType>
DType clamp(DType d, DType minValue, DType maxValue) {
	return min(maxValue, max(d, minValue));
}

f32 to_radians(f32 degree);
f32 to_degree(f32 radians);
// solve ray-tracing quadratic, only success when we have 2 real solutions
const bool solve_rtquadratic(f32 A, f32 B, f32 C, f32& t0, f32& t1);

// compute crc32 naive way
const u32 compute_crc32_naive(const_cstr nullTerminatedStr);

const size32 next_pow2(const size32 i_value32);
const size64 next_pow2(const size64 i_value64);

}
