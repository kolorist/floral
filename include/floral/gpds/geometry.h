#pragma once

#include "floral/stdaliases.h"

#include "vec.h"
#include "mat.h"

#include <float.h>

namespace floral {

template <class DType>
struct ray2d
{
	ray2d() = default;

	ray2d(const vec2<DType>& i_o, const vec2<DType>& i_d)
		: o(i_o)
		, d(i_d)
		, mint(0.0f)
		, maxt(FLT_MAX)
	{
	}

	ray2d(const vec2<DType>& i_o, const vec2<DType>& i_d, const f32 i_mint, const f32 i_maxt)
		: o(i_o)
		, d(i_d)
		, mint(i_mint)
		, maxt(i_maxt)
	{
	}

	vec2<DType> get_point(const f32 t) const
	{
		return o + t * d;
	}
	//--------------------------------------
	vec2<DType>									o;
	vec2<DType>									d;
	f32											mint;
	f32											maxt;
};

template <class DType>
struct ray3d
{
	ray3d() = default;

	ray3d(const vec3<DType>& i_o, const vec3<DType>& i_d)
		: o(i_o)
		, d(i_d)
		, mint(0.0f)
		, maxt(FLT_MAX)
	{
	}

	ray3d(const vec3<DType>& i_o, const vec3<DType>& i_d, const f32 i_mint, const f32 i_maxt)
		: o(i_o)
		, d(i_d)
		, mint(i_mint)
		, maxt(i_maxt)
	{
	}

	vec3<DType> get_point(const f32 t) const
	{
		return o + t * d;
	}
	//--------------------------------------
	vec3<DType>									o;
	vec3<DType>									d;
	f32											mint;
	f32											maxt;
};
////////////////////////////////////////////
using ray2df = ray2d<f32>;
using ray3df = ray3d<f32>;

////////////////////////////////////////////
// 2d shape
struct circle {
};

// 3d shape
template <class ShapeType>
struct shape3d {
	shape3d() = default;

	shape3d(const mat4x4f& l2w, const mat4x4f& w2l)
		: localToWorld(l2w)
		, worldToLocal(w2l)
	{ }

	const bool ray_intersect(const ray3df& r, f32 *tHit, f32 *rayEpsilon) {
		return (ShapeType*)(this)->ray_intersect(r, tHit, rayEpsilon);
	}

	//--------------------------------------
	mat4x4f 								localToWorld;
	mat4x4f 								worldToLocal;
};

struct sphere : public shape3d<sphere> {
	sphere() = default;

	sphere(const mat4x4f& l2w, const mat4x4f& w2l,
			f32 r, f32 z0, f32 z1, f32 pm);

	const bool ray_intersect(const ray3df& r, f32 *o_tHit, f32 *o_rayEpsilon) const;
	//--------------------------------------
	f32 									radius;
	f32 									phiMax;
	f32 									zMin, zMax;
	f32 									thetaMin, thetaMax;
};

};
