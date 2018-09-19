#pragma once

#include "gpds/vec.h"

namespace floral {

floral::vec3f texel_coord_to_cube_coord(const s32 i_faceIdx, const f32 i_u, const f32 i_v, const s32 i_size);
f32 texel_coord_to_solid_angle(const s32 i_faceIdx, const f32 i_u, const f32 i_v, const s32 i_size);

}