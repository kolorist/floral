#pragma once

#include "floral/stdaliases.h"

namespace floral
{

class rng
{
private:
	static constexpr u64 k_PCG32_default_state		= 0x853c49e6748fea9bULL;
	static constexpr u64 k_PCG32_default_stream		= 0xda3e39cb94b95bdbULL;
	static constexpr u64 k_PCG32_mult				= 0x5851f42d4c957f2dULL;

	static constexpr f32 k_f32_one_minus_epsilon	= 0.99999994f;
	static constexpr f64 k_f64_one_minus_epsilon	= 0.99999999999999989;

public:
	rng() = delete;
	rng(u64 i_sequenceIndex);

	void										set_sequence(u64 i_sequenceIndex);
	const u32									get_u32();
	const u32									get_u32(u32 i_modulo);
	const f32									get_f32();
	const f64									get_f64();

private:
	u64											m_state;
	u64											m_inc;
};

}

#include "rng.inl"
