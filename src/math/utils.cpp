#include "floral/math/utils.h"

#include <math.h>
#include <cstring>
#include <algorithm>

namespace floral
{
// ---------------------------------------------

f32 to_radians(f32 degree)
{
	return (degree / 180.0f * pi);
}

// ---------------------------------------------

f32 to_degree(f32 radians)
{
	return (radians / pi * 180.0f);
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

const size32 next_pow2(const size32 i_value32)
{
	// run-time reallocate => round (up) to the nearest power of 2
	// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
	size32 po2Value = i_value32;
	po2Value--;
	po2Value |= po2Value >> 1;
	po2Value |= po2Value >> 2;
	po2Value |= po2Value >> 4;
	po2Value |= po2Value >> 8;
	po2Value |= po2Value >> 16;
	po2Value++;
	return po2Value;
}

const size64 next_pow2(const size64 i_value64)
{
	size64 po2Value = i_value64;
	po2Value--;
	po2Value |= po2Value >> 1;
	po2Value |= po2Value >> 2;
	po2Value |= po2Value >> 4;
	po2Value |= po2Value >> 8;
	po2Value |= po2Value >> 16;
	po2Value |= po2Value >> 32;
	po2Value++;
	return po2Value;
}

// ---------------------------------------------
}
