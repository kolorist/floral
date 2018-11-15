#include "gpds/geometry.h"

#include <math.h>

#include <math/utils.h>

namespace floral {

sphere::sphere(const mat4x4f& l2w, const mat4x4f& w2l,
		f32 r, f32 z0, f32 z1, f32 pm)
	: shape3d(l2w, w2l)
{ 
	radius = r;
	zMin = clamp(min(z0, z1), -radius, radius);
	zMax = clamp(max(z0, z1), -radius, radius);
	thetaMin = cosf(clamp(zMin / radius, -1.0f, 1.0f));
	thetaMax = cosf(clamp(zMax / radius, -1.0f, 1.0f));
	phiMax = to_radians(clamp(pm, 0.0f, 360.0f));
}

const bool sphere::ray_intersect(const ray3df& r, f32 *tHit, f32 *rayEpsilon)
{
	// transform ray to local space
	// compute quadratic sphere coeffs
	// solve quadratic equation for t
	// compute sphere hit position and phi
	// test sphere intersect against clipping regions
	// find parametric representation of sphere hit
	// init differential geoemtry from parametric information
	// update tHit for quadratic intersection
	// compute rayEpsilon for quadratic intersection
	return true;
}

}
