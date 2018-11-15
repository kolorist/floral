#pragma once

#include <stdaliases.h>
#include "gpds/vec.h"
#include "gpds/geometry.h"

namespace floral {

const bool										ray_triangle_intersect(const ray3df& i_ray,
													const floral::vec3f& i_p0, const floral::vec3f& i_p1, const floral::vec3f& i_p2,
													f32* o_t);

};
