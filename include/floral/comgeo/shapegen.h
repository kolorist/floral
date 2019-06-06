#pragma once

#include "floral/stdaliases.h"

namespace floral
{

// assumptions:
// - vertex position: 2d / 3d vector of f32(s)
// - vertex normal: 2d / 3d vector of f32(s)
// - texture coordinates: 2d / 3d vector of f32(s)

struct geo_generate_result_t
{
	u32 vertices_generated;
	u32 indices_generated;
};

geo_generate_result_t							generate_unit_box_3d(const s32 i_startIdx, const size i_vtxStride, voidptr o_vtxData, s32* o_idxData);

}
