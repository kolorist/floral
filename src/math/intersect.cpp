#include "floral/math/intersect.h"

#include <math.h>

namespace floral {

//----------------------------------------------

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

//----------------------------------------------

const bool ray_quad_intersect(const ray3df& i_ray,
		const floral::vec3f& i_p0, const floral::vec3f& i_p1,
		const floral::vec3f& i_p2, const floral::vec3f& i_p3, f32* o_t)
{
	f32 t = 0.0f;
	bool hitTriangle1 = ray_triangle_intersect(i_ray, i_p0, i_p1, i_p2, &t);
	if (hitTriangle1) {
		*o_t = t;
		return true;
	}

	bool hitTriangle2 = ray_triangle_intersect(i_ray, i_p2, i_p3, i_p0, &t);
	if (hitTriangle2) {
		*o_t = t;
		return true;
	}
	return false;
}

//----------------------------------------------

#include "tri_aabb_intersect.inl"

const bool triangle_aabb_intersect(
		const floral::vec3f& i_v0, const floral::vec3f& i_v1,
		const floral::vec3f& i_v2, const floral::aabb3f& i_aabb)
{
	floral::vec3f translation = -(i_aabb.min_corner + i_aabb.max_corner) / 2.0f;
	floral::vec3f scaling = i_aabb.max_corner - i_aabb.min_corner;

	floral::vec3f v0 = (i_v0 + translation) / scaling;
	floral::vec3f v1 = (i_v1 + translation) / scaling;
	floral::vec3f v2 = (i_v2 + translation) / scaling;

	Triangle3 tri;
	tri.v1 = Point3 { v0.x, v0.y, v0.z};
	tri.v2 = Point3 { v1.x, v1.y, v1.z};
	tri.v3 = Point3 { v2.x, v2.y, v2.z};

	long intersect = t_c_intersection(tri);
	if (intersect == INSIDE)
		return true;
	else
		return false;
}

}
