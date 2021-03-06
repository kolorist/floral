#pragma once

#include "floral/stdaliases.h"
#include "floral/gpds/vec.h"
#include "floral/gpds/geometry.h"
#include "floral/gpds/rect.h"

namespace floral {

const bool										ray_triangle_intersect(const ray3df& i_ray,
													const floral::vec3f& i_p0, const floral::vec3f& i_p1, const floral::vec3f& i_p2, f32* o_t);
													
const bool										ray_triangle_intersect(const ray3df& i_ray,
													const floral::vec3f& i_p0, const floral::vec3f& i_p1, const floral::vec3f& i_p2, f32* o_t, f32* o_b0, f32* o_b1);

const bool										ray_quad_intersect(const ray3df& i_ray,
													const floral::vec3f& i_p0, const floral::vec3f& i_p1,
													const floral::vec3f& i_p2, const floral::vec3f& i_p3,
													f32* o_t);

const bool										triangle_aabb_intersect(
													const floral::vec3f& i_v0, const floral::vec3f& i_v1,
													const floral::vec3f& i_v2, const floral::aabb3f& i_aabb);
													
const bool										point_inside_aabb(
													const floral::vec3f& i_p, const floral::aabb3f& i_aabb);
													
const bool										point_in_positive_region_of_plane(
													const floral::vec3f& i_p, const floral::vec3f& i_p0, const floral::vec3f& i_normal);

};
