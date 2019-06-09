#pragma once

#include "floral/stdaliases.h"
#include "floral/gpds/mat.h"

namespace floral
{

// assumptions:
// - vertex position: 2d / 3d vector of f32(s)
// - vertex normal: 2d / 3d vector of f32(s)
// - texture coordinates: 2d / 3d vector of f32(s)

enum class geo_vertex_format_e : s32
{
	position									= 1,
	normal										= position << 1,
	tex_coord									= normal << 1
};

inline s32 operator|(const geo_vertex_format_e i_lhs, const geo_vertex_format_e i_rhs)
{
	return ((s32)i_lhs | (s32)i_rhs);
}

struct geo_generate_result_t
{
	u32 vertices_generated;
	u32 indices_generated;
};

struct manifold_geo_generate_result_t
{
	u32 vertices_generated;
	u32 indices_generated;
	u32 manifold_vertices_generated;
	u32 manifold_indices_generated;
};

void											push_generation_transform(const floral::mat4x4f& i_xform);
void											pop_generation_transform();
void											reset_generation_transforms_stack();

// transformation stack will affect these functions
geo_generate_result_t							generate_quadtes_plane_3d(
													const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat,
													const f32 i_quadSize, voidptr o_vtxData, s32* o_idxData);

//----------------------------------------------

geo_generate_result_t							generate_unit_plane_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData);
geo_generate_result_t							generate_unit_box_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData);
geo_generate_result_t							generate_unit_icosphere_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData);

//----------------------------------------------

manifold_geo_generate_result_t					generate_manifold_quadtes_unit_plane_3d(
													const s32 i_startIdx, const size i_vtxStride,
													const s32 i_vtxFormat, const f32 i_quadSize, voidptr o_vtxData, s32* o_idxData,
													const s32 i_mnfStartIdx, const size i_mnfVtxStride, const f32 i_mnfThickness,
													const s32 i_mnfVtxFormat, voidptr o_mnfVtxData, s32* o_mnfIdxData);

manifold_geo_generate_result_t					generate_manifold_unit_plane_3d(
													const s32 i_startIdx, const size i_vtxStride,
													const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData,
													const s32 i_mnfStartIdx, const size i_mnfVtxStride, const f32 i_mnfThickness,
													const s32 i_mnfVtxFormat, voidptr o_mnfVtxData, s32* o_mnfIdxData);

//----------------------------------------------
// built-in geometry

}
