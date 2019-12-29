#include "floral/gpds/geometry.h"

#include "floral/math/utils.h"

#include <math.h>

namespace floral
{

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

const bool sphere::ray_intersect(const ray3df& r, f32 *o_tHit, f32 *o_rayEpsilon) const
{
	f32 phi;
	vec3f pHit;
	// transform ray to local space
	ray3df ray;
	ray.mint = r.mint;
	ray.maxt = r.maxt;
	vec4f localRayOrigin = worldToLocal * floral::vec4f(r.o, 1.0f);
	vec4f localRayDir = worldToLocal * floral::vec4f(r.d, 0.0f);
	ray.o = vec3f(localRayOrigin.x, localRayOrigin.y, localRayOrigin.z);
	ray.d = vec3f(localRayDir.x, localRayDir.y, localRayDir.z);
	// compute quadratic sphere coeffs
	f32 qA = ray.d.x * ray.d.x + ray.d.y * ray.d.y + ray.d.z * ray.d.z;
	f32 qB = 2.0f * (ray.d.x * ray.o.x + ray.d.y * ray.o.y + ray.d.z * ray.o.z);
	f32 qC = ray.o.x * ray.o.x + ray.o.y * ray.o.y + ray.o.z * ray.o.z - radius * radius;
	// solve quadratic equation for t
	f32 t0, t1;
	if (!solve_rtquadratic(qA, qB, qC, t0, t1))
	{
		return false;
	}
	// compute intersection distance along ray
	if (t0 > ray.maxt || t1 < ray.mint)
	{
		return false;
	}
	f32 tHit = t0;
	if (t0 < ray.mint)
	{
		tHit = t1;
		if (tHit > ray.maxt)
		{
			return false;
		}
	}
	// compute sphere hit position and phi
	pHit = ray.get_point(tHit);
	if (pHit.x == 0.0f && pHit.y == 0.0f)
	{
		pHit.x = 1e-5f * radius;
	}
	phi = atan2f(pHit.y, pHit.x);
	if (phi < 0.0f)
	{
		phi += 2.0f * pi;
	}
	// test sphere intersect against clipping regions
	if ((zMin > -radius && pHit.z < zMin) ||
		(zMax <  radius && pHit.z > zMax) || phi > phiMax)
	{
		if (tHit == t1)
		{
			return false;
		}
		if (t1 > ray.maxt)
		{
			return false;
		}
		tHit = t1;
		// compute sphere hit position and phi (copied from above)
		pHit = ray.get_point(tHit);
		if (pHit.x == 0.0f && pHit.y == 0.0f)
		{
			pHit.x = 1e-5f * radius;
		}
		phi = atan2f(pHit.y, pHit.x);
		if (phi < 0.0f)
		{
			phi += 2.0f * pi;
		}
		if ((zMin > -radius && pHit.z < zMin) ||
			(zMax <  radius && pHit.z > zMax) || phi > phiMax)
		{
			return false;
		}
	}
	// TODO: find parametric representation of sphere hit
	// TODO: init differential geoemtry from parametric information
	// update tHit for quadratic intersection
	*o_tHit = tHit;
	// compute rayEpsilon for quadratic intersection
	*o_rayEpsilon = 5e-4f * tHit;
	return true;
}

}
