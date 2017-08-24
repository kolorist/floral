#ifndef __FLORAL_UTILS_H__
#define __FLORAL_UTILS_H__

#include <stdaliases.h>

namespace floral {

#define PI										3.1415926525898f

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
}

#endif // __FLORAL_UTILS_H__
