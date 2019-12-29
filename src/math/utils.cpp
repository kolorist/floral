#include "floral/math/utils.h"

#include <math.h>
#include <cstring>
#include <algorithm>

namespace floral
{
// ---------------------------------------------

f32 to_radians(f32 degree)
{
	return (degree / 180.0f * PI);
}

// ---------------------------------------------

f32 to_degree(f32 radians)
{
	return (radians / PI * 180.0f);
}

// ---------------------------------------------

const bool solve_rtquadratic(f32 A, f32 B, f32 C, f32& t0, f32& t1)
{
	f32 delta = B * B - 4 * A * C;
	if (delta <= 0.0f)
	{
		return false;
	}
	f32 sqrtDelta = sqrtf(delta);
	// we did this to reduce cancellation error when B -> +-sqrtDelta
	f32 q;
	if (B < 0)
	{
		q = -0.5f * (B - sqrtDelta);
	}
	else
	{
		q = -0.5f * (B + sqrtDelta);
	}
	t0 = q / A;
	t1 = C / q;
	if (t0 > t1)
	{
		std::swap(t0, t1);
	}
	return true;
}

// ---------------------------------------------

const u32 compute_crc32_naive(const_cstr nullTerminatedStr)
{
	static const u32 k_CRCWidth = 32;
	static const u32 k_CRCTopBit = 1 << (k_CRCWidth - 1);
	static const u32 k_Polynomial = 0xD8;

	const size strLen = strlen(nullTerminatedStr);
	u32 remainder = 0;

	for (size byte = 0; byte < strLen; byte++) {
		remainder ^= (nullTerminatedStr[byte] << (k_CRCWidth - 8));
		for (u8 bit = 8; bit > 0; bit--) {
			if (remainder & k_CRCTopBit) {
				remainder = (remainder << 1) ^ k_Polynomial;
			}
			else {
				remainder = (remainder << 1);
			}
		}
	}

	return remainder;
}

// ---------------------------------------------
}
