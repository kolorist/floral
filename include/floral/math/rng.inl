#include "utils.h"

namespace floral
{

inline rng::rng(u64 i_sequenceIndex)
{
	set_sequence(i_sequenceIndex);
}

inline void rng::set_sequence(u64 i_sequenceIndex)
{
	m_state = 0u;
	m_inc = (i_sequenceIndex << 1u) | 1u;
	get_u32();
	m_state += k_PCG32_default_state;
	get_u32();
}

inline const u32 rng::get_u32()
{
	u64 oldstate = m_state;
	m_state = oldstate * k_PCG32_mult + m_inc;
	u32 xorshifted = (u32)(((oldstate >> 18u) ^ oldstate) >> 27u);
	u32 rot = (u32)(oldstate >> 59u);
	return (xorshifted >> rot) | (xorshifted << ((~rot + 1u) & 31));
}

inline const u32 rng::get_u32(u32 i_modulo)
{
	u32 threshold = (~i_modulo + 1u) % i_modulo;
	while (true)
	{
		u32 r = get_u32();
		if (r >= threshold)
		{
			return r % i_modulo;
		}
	}
}

inline const f32 rng::get_f32()
{
	return min(k_f32_one_minus_epsilon,
			f32(get_u32() * 2.3283064365386963e-10f));
}

inline const f64 rng::get_f64()
{
	return min(k_f64_one_minus_epsilon,
			f64(get_u32() * 2.3283064365386963e-10f));
}

}
