#pragma once

#include "floral/stdaliases.h"
#include "floral/gpds/vec.h"
#include "floral/gpds/geometry.h"

namespace floral {

const bool										ray_triangle_intersect(const ray3df& i_ray,
													const floral::vec3f& i_p0, const floral::vec3f& i_p1, const floral::vec3f& i_p2, f32* o_t);

const bool										ray_quad_intersect(const ray3df& i_ray,
													const floral::vec3f& i_p0, const floral::vec3f& i_p1,
													const floral::vec3f& i_p2, const floral::vec3f& i_p3,
													f32* o_t);

};
