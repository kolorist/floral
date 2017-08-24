#include "math/utils.h"

#include <math.h>

namespace floral {
	f32 to_radians(f32 degree) {
		return (degree / 180.0f * PI);
	}

	f32 to_degree(f32 radians) {
		return (radians / PI * 180.0f);
	}

	const bool solve_rtquadratic(f32 A, f32 B, f32 C, f32& t0, f32& t1)
	{
		f32 delta = B * B - 4 * A * C;
		if (delta <= 0.0f)
			return false;
		f32 sqrtDelta = sqrtf(delta);
		// we did this to reduce cancellation error when B -> +-sqrtDelta
		f32 q = B < 0 ? (-0.5f * (B - sqrtDelta)) : (-0.5f * (B + sqrtDelta));
		t0 = q / A;
		t1 = C / q;
		return true;
	}
}
