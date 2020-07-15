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

const u32 next_pow2(const u32 i_value32)
{
	// run-time reallocate => round (up) to the nearest power of 2
	// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
	u32 po2Value = i_value32;
	po2Value--;
	po2Value |= po2Value >> 1;
	po2Value |= po2Value >> 2;
	po2Value |= po2Value >> 4;
	po2Value |= po2Value >> 8;
	po2Value |= po2Value >> 16;
	po2Value++;
	return po2Value;
}

const s32 next_pow2(const s32 i_value32)
{
	return (s32)next_pow2(u32(i_value32));
}

const u64 next_pow2(const u64 i_value64)
{
	u64 po2Value = i_value64;
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

const s64 next_pow2(const s64 i_value64)
{
	return (s64)next_pow2(u64(i_value64));
}

f16 float_to_half_full(f32 i_value)
{
	// source: https://gist.github.com/rygorous/2156668
	union fp16
	{
		u16 u;
		struct
		{
			u32 mantissa : 10;
			u32 exponent : 5;
			u32 sign : 1;
		};
	};
	
	union fp32
	{
		u32 u;
		f32 f;
		struct
		{
			u32 mantissa : 23;
			u32 exponent : 8;
			u32 sign : 1;
		};
	};
	
    fp16 o = { 0 };
	fp32 f;
	f.f = i_value;

    // Based on ISPC reference code (with minor modifications)
    if (f.exponent == 0) // Signed zero/denormal (which will underflow)
        o.exponent = 0;
    else if (f.exponent == 255) // Inf or NaN (all exponent bits set)
    {
        o.exponent = 31;
        o.mantissa = f.mantissa ? 0x200 : 0; // NaN->qNaN and Inf->Inf
    }
    else // Normalized number
    {
        // exponent unbias the single, then bias the halfp
        int newexp = f.exponent - 127 + 15;
        if (newexp >= 31) // Overflow, return signed infinity
            o.exponent = 31;
        else if (newexp <= 0) // Underflow
        {
            if ((14 - newexp) <= 24) // mantissa might be non-zero
            {
                u32 mant = f.mantissa | 0x800000; // Hidden 1 bit
                o.mantissa = mant >> (14 - newexp);
                if ((mant >> (13 - newexp)) & 1) // Check for rounding
                    o.u++; // Round, might overflow into exp bit, but this is OK
            }
        }
        else
        {
            o.exponent = newexp;
            o.mantissa = f.mantissa >> 13;
            if (f.mantissa & 0x1000) // Check for rounding
                o.u++; // Round, might overflow to inf, this is OK
        }
    }

    o.sign = f.sign;
    return o.u;
}

// ---------------------------------------------
}
