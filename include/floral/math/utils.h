#pragma once

#include <string.h>

#include "floral/stdaliases.h"

#include "floral/types/condition.h"

namespace floral
{

constexpr f32 pi = 3.1415926525898f;
constexpr f32 half_pi = 1.5707963267948966f;

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

template <class t_type>
t_type min(t_type lhs, t_type rhs)
{
	return (lhs > rhs ? rhs : lhs);
}

template <class t_type>
t_type max(t_type lhs, t_type rhs)
{
	return (lhs > rhs ? lhs : rhs);
}

template <class t_type>
t_type clamp(t_type d, t_type minValue, t_type maxValue)
{
	return min(maxValue, max(d, minValue));
}

template<typename t_type>
t_type smoothstep(t_type edge0, t_type edge1, t_type x)
{
  x = clamp((x - edge0) / (edge1 - edge0), t_type(0.0f), t_type(1.0f));
  return x * x * (3.0f - 2.0f * x);
}

f32 to_radians(f32 degree);
f32 to_degree(f32 radians);
// solve ray-tracing quadratic, only success when we have 2 real solutions
const bool solve_rtquadratic(f32 A, f32 B, f32 C, f32& t0, f32& t1);

// compute crc32 naive way
const u32 compute_crc32_naive(const_cstr nullTerminatedStr);

const u32 next_pow2(const u32 i_value32);
const s32 next_pow2(const s32 i_value32);
const u64 next_pow2(const u64 i_value64);
const s64 next_pow2(const s64 i_value64);

template <class t_type>
inline const bool test_bit_pos(const t_type i_bitSet, const size i_pos)
{
	using RoundedType = conditional_t<sizeof(t_type) < sizeof(u32), u32, u64>;
	return (RoundedType(i_bitSet) & (RoundedType(1) << i_pos)) != 0;
}

template <class t_type>
inline const bool test_bit_mask(const t_type i_bitSet, const t_type i_bitMask)
{
	using RoundedType = conditional_t<sizeof(t_type) < sizeof(u32), u32, u64>;
	return (RoundedType(i_bitSet) & RoundedType(i_bitMask)) != 0;
}

f16 float_to_half_full(f32 i_value);

}
