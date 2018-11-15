#include "math/intersect.h"

namespace floral {

const bool ray_triangle_intersect(const ray3df& i_ray,
		const floral::vec3f& i_p0, const floral::vec3f& i_p1, const floral::vec3f& i_p2, f32* o_t)
{
	vec3f e1 = i_p1 - i_p0;
	vec3f e2 = i_p2 - i_p0;
	vec3f s1 = cross(i_ray.d, e2);
	f32 divisor = dot(s1, e1);
	if (divisor == 0.0f)
		return false;

	f32 invDivisor = 1.0f / divisor;

	// first barycentric coordinate
	vec3f d = i_ray.o - i_p0;
	f32 b1 = dot(d, s1) * invDivisor;
	if (b1 < 0.0f || b1 > 1.0f)
		return false;

	// second barycentric coordinate
	vec3f s2 = cross(d, e1);
	f32 b2 = dot(i_ray.d, s2) * invDivisor;
	if (b2 < 0.0f || b1 + b2 > 1.0f)
		return false;

	// t to intersection point
	*o_t = dot(e2, s2) * invDivisor;

	return true;
}

}
