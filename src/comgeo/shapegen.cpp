#include "floral/comgeo/shapegen.h"

#include "floral/math/utils.h"
#include "floral/assert/assert.h"
#include "floral/gpds/vec.h"
#include "floral/containers/array.h"

namespace floral
{

/*
 * 			| y
 * 			|
 * 			|
 * 			*-------x
 * 		   /
 * 		  /
 * 		 / z
 */

struct vertex_pn_t
{
	floral::vec3f position;
	floral::vec3f normal;
};

static floral::mat4x4f s_xformStack[16];
static size s_topXForm = 0;

static const f32 s_epsilon = 0.001f;

inline bool compare_vec3f_point(const floral::vec3f& i_a, const floral::vec3f& i_b)
{
	return (floral::length(i_a - i_b) <= s_epsilon);
}

inline bool compare_vec3f_dir(const floral::vec3f& i_a, const floral::vec3f& i_b)
{
	floral::vec3f c = floral::cross(i_a, i_b);
	f32 d = floral::dot(i_a, i_b);
	return (floral::length(c) <= s_epsilon && d >= 0.0f);
}

inline bool compare_vertex_pn(const vertex_pn_t& i_a, const vertex_pn_t& i_b)
{
	return (compare_vec3f_point(i_a.position, i_b.position)
			&& compare_vec3f_dir(i_a.normal, i_b.normal));
}

//----------------------------------------------

void push_generation_transform(const floral::mat4x4f& i_xform)
{
	FLORAL_ASSERT_MSG(s_topXForm < 16, "Exceeded maximum of transform stack");
	s_xformStack[s_topXForm] = i_xform;
	s_topXForm++;
}

void pop_generation_transform()
{
	FLORAL_ASSERT_MSG(s_topXForm > 0, "Cannot pop transform from stack anymore");
	s_topXForm--;
}

void reset_generation_transforms_stack()
{
	s_topXForm = 0;
}

void apply_tranforms(const s32 i_vtxFormat, const u32 i_vtxCount, const size i_vtxStride, voidptr io_vtxData)
{
	if (s_topXForm == 0)
	{
		return;
	}

	floral::mat4x4f m(1.0f);

	for (size i = 0; i < s_topXForm; i++)
	{
		m = m * s_xformStack[i];
	}

	aptr vtxData = (aptr)io_vtxData;

	if (TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::normal))
	{
		for (u32 i = 0; i < i_vtxCount; i++)
		{
			vertex_pn_t* vtx = (vertex_pn_t*)vtxData;

			floral::vec4f hPos(vtx->position.x, vtx->position.y, vtx->position.z, 1.0f);
			floral::vec4f hNorm(vtx->normal.x, vtx->normal.y, vtx->normal.z, 0.0f);
			hPos = m * hPos;
			hNorm = m * hNorm;
			vtx->position = floral::vec3f(hPos.x, hPos.y, hPos.z);
			vtx->normal = floral::normalize(floral::vec3f(hNorm.x, hNorm.y, hNorm.z));

			vtxData += i_vtxStride;
		}
	}
	else
	{
		for (u32 i = 0; i < i_vtxCount; i++)
		{
			floral::vec3f* pos = (floral::vec3f*)vtxData;

			floral::vec4f hPos(pos->x, pos->y, pos->z, 1.0f);
			hPos = m * hPos;
			*pos = floral::vec3f(hPos.x, hPos.y, hPos.z);

			vtxData += i_vtxStride;
		}
	}
}

//----------------------------------------------

geo_generate_result_t generate_quadtes_unit_plane_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, const f32 i_quadSize, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");

	s32 tesTime = (s32)(-logf(i_quadSize) / logf(2.0f));	// for 1.0f width
	s32 gridPerEdge = 1 << (tesTime + 1);					// for 2.0f width
	f32 gridSize = 2.0f / gridPerEdge;

	floral::inplace_array<floral::vec3f, 1024u> vertexArray;
	floral::inplace_array<s32, 4096u> indexArray;

	static const s32 indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	for (s32 i = 0; i < gridPerEdge; i++)
	{
		for (s32 j = 0; j < gridPerEdge; j++)
		{
			floral::vec3f v[4];
			v[0] = floral::vec3f(1.0f - gridSize * i, 0.0f, 1.0f - gridSize * j);
			v[1] = floral::vec3f(1.0f - gridSize * i, 0.0f, 1.0f - gridSize * (j + 1));
			v[2] = floral::vec3f(1.0f - gridSize * (i + 1), 0.0f, 1.0f - gridSize * (j + 1));
			v[3] = floral::vec3f(1.0f - gridSize * (i + 1), 0.0f, 1.0f - gridSize * j);

			for (u32 k = 0; k < 6; k++)
			{
				u32 index = vertexArray.find(v[indices[k]], &compare_vec3f_point);
				if (index == vertexArray.get_terminated_index())
				{
					vertexArray.push_back(v[indices[k]]);
					indexArray.push_back(vertexArray.get_size() - 1);
				}
				else
				{
					indexArray.push_back(index);
				}
			}
		}
	}

	if (TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::normal))
	{
		for (u32 i = 0; i < vertexArray.get_size(); i++)
		{
			vertex_pn_t* vtx = (vertex_pn_t*)o_vtxData;
			vtx->position = vertexArray[i];
			vtx->normal = floral::vec3f(0.0f, 1.0f, 0.0f);
			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}
	}
	else
	{
		for (u32 i = 0; i < vertexArray.get_size(); i++)
		{
			floral::vec3f* pos = (floral::vec3f*)o_vtxData;
			*pos = vertexArray[i];
			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}
	}

	for (u32 i = 0; i < indexArray.get_size(); i++)
	{
		o_idxData[i] = i_startIdx + indexArray[i];
	}

	geo_generate_result_t genResult;
	genResult.vertices_generated = vertexArray.get_size();
	genResult.indices_generated = indexArray.get_size();
	return genResult;
}

geo_generate_result_t generate_quadtes_unit_box_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, const f32 i_quadSize, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");
}

//----------------------------------------------

geo_generate_result_t generate_unit_plane_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");

	static const floral::vec3f vertices[] =
	{
		floral::vec3f(1.0f, 0.0f, 1.0f),
		floral::vec3f(1.0f, 0.0f, -1.0f),
		floral::vec3f(-1.0f, 0.0f, -1.0f),
		floral::vec3f(-1.0f, 0.0f, 1.0f)
	};

	static const s32 indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	geo_generate_result_t genResult;;

	if (TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::normal))
	{
		for (size i = 0; i < 4; i++)
		{
			vertex_pn_t* vtx = (vertex_pn_t*)o_vtxData;
			vtx->position = vertices[i];
			vtx->normal = floral::vec3f(0.0f, 1.0f, 0.0f);

			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}

		for (size i = 0; i < 6; i++)
		{
			o_idxData[i] = i_startIdx + indices[i];
		}

		genResult.vertices_generated = 4;
		genResult.indices_generated = 6;
		return genResult;
	}
	else
	{
		for (size i = 0; i < 4; i++)
		{
			floral::vec3f* pos = (floral::vec3f*)o_vtxData;
			*pos = vertices[i];

			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}

		for (size i = 0; i < 6; i++)
		{
			o_idxData[i] = i_startIdx + indices[i];
		}

		genResult.vertices_generated = 4;
		genResult.indices_generated = 6;
		return genResult;
	}
}

geo_generate_result_t generate_unit_box_3d_no_normals(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");
	FLORAL_ASSERT(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::normal) == 0);

	static const floral::vec3f vertices[] =
	{
		floral::vec3f(1.0f, -1.0f, 1.0f),
		floral::vec3f(1.0f, -1.0f, -1.0f),
		floral::vec3f(-1.0f, -1.0f, -1.0f),
		floral::vec3f(-1.0f, -1.0f, 1.0f),

		floral::vec3f(1.0f, 1.0f, 1.0f),
		floral::vec3f(1.0f, 1.0f, -1.0f),
		floral::vec3f(-1.0f, 1.0f, -1.0f),
		floral::vec3f(-1.0f, 1.0f, 1.0f)
	};

	static const s32 indices[] =
	{
		0, 3, 2,	// -Y
		2, 1, 0,	// -Y
		4, 5, 6,	// +Y
		6, 7, 4,	// +Y
		6, 2, 3,	// -X
		3, 7, 6,	// -X
		4, 0, 1,	// +X
		1, 5, 4,	// +X
		5, 1, 2,	// -Z
		2, 6, 5,	// -Z
		3, 0, 4,	// +Z
		4, 7, 3,	// +Z
	};

	for (size i = 0; i < 8; i++)
	{
		floral::vec3f* pos = (floral::vec3f*)o_vtxData;
		*pos = vertices[i];

		o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
	}

	for (size i = 0; i < 36; i++)
	{
		o_idxData[i] = i_startIdx + indices[i];
	}

	geo_generate_result_t genResult;
	genResult.vertices_generated = 8;
	genResult.indices_generated = 36;
	return genResult;
}

geo_generate_result_t generate_unit_box_3d_with_normals(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");
	FLORAL_ASSERT_MSG(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::normal) != 0, "Vertex format must contain normal semantic");
	FLORAL_ASSERT_MSG(sizeof(vertex_pn_t) <= i_vtxStride, "Vertex stride must be greater than sizeof(vertex_pn_t)");

	static const floral::vec3f vertices[] =
	{
		floral::vec3f(1.0f, -1.0f, 1.0f),
		floral::vec3f(1.0f, -1.0f, -1.0f),
		floral::vec3f(-1.0f, -1.0f, -1.0f),
		floral::vec3f(-1.0f, -1.0f, 1.0f),

		floral::vec3f(1.0f, 1.0f, 1.0f),
		floral::vec3f(1.0f, 1.0f, -1.0f),
		floral::vec3f(-1.0f, 1.0f, -1.0f),
		floral::vec3f(-1.0f, 1.0f, 1.0f)
	};

	static const s32 indices[] =
	{
		0, 3, 2,	// -Y
		2, 1, 0,	// -Y
		4, 5, 6,	// +Y
		6, 7, 4,	// +Y
		6, 2, 3,	// -X
		3, 7, 6,	// -X
		4, 0, 1,	// +X
		1, 5, 4,	// +X
		5, 1, 2,	// -Z
		2, 6, 5,	// -Z
		3, 0, 4,	// +Z
		4, 7, 3,	// +Z
	};

	static const floral::vec3f faceNormals[] =
	{
		floral::vec3f(0.0f, -1.0f, 0.0f),
		floral::vec3f(0.0f, 1.0f, 0.0f),
		floral::vec3f(-1.0f, 0.0f, 0.0f),
		floral::vec3f(1.0f, 0.0f, 0.0f),
		floral::vec3f(0.0f, 0.0f, -1.0f),
		floral::vec3f(0.0f, 0.0f, 1.0f)
	};

	floral::inplace_array<vertex_pn_t, 36u> vertexArray;
	floral::inplace_array<s32, 36u> indexArray;

	for (s32 f = 0; f < 6; f++)
	{
		for (s32 i = 0; i < 6; i++)
		{
			s32 idx = f * 6 + i;
			vertex_pn_t vtx;
			vtx.position = vertices[indices[idx]];
			vtx.normal = faceNormals[f];

			const u32 oldIdx = vertexArray.find(vtx, &compare_vertex_pn);
			if (oldIdx == vertexArray.get_terminated_index())
			{
				vertexArray.push_back(vtx);
				indexArray.push_back(vertexArray.get_size() - 1);
			}
			else
			{
				indexArray.push_back(oldIdx);
			}
		}
	}

	for (u32 i = 0; i < vertexArray.get_size(); i++)
	{
		vertex_pn_t* vtx = (vertex_pn_t*)o_vtxData;
		*vtx = vertexArray[i];
		o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
	}

	for (u32 i = 0; i < indexArray.get_size(); i++)
	{
		o_idxData[i] = i_startIdx + indexArray[i];
	}

	geo_generate_result_t genResult;
	genResult.vertices_generated = vertexArray.get_size();
	genResult.indices_generated = indexArray.get_size();
	return genResult;
}

geo_generate_result_t generate_unit_box_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	if (TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::normal))
	{
		return generate_unit_box_3d_with_normals(i_startIdx, i_vtxStride, i_vtxFormat, o_vtxData, o_idxData);
	}
	else
	{
		return generate_unit_box_3d_no_normals(i_startIdx, i_vtxStride, i_vtxFormat, o_vtxData, o_idxData);
	}
}

//----------------------------------------------

static void tesselate_icosphere(
		floral::inplace_array<floral::vec3f, 1024u>& i_fromVtx,
		floral::inplace_array<u32, 4096u>& i_fromIdx,
		floral::inplace_array<floral::vec3f, 1024u>& o_toVtx,
		floral::inplace_array<u32, 4096u>& o_toIdx)
{
	o_toVtx.empty();
	o_toIdx.empty();

	static const u32 tmpIdx[12] = {
		0,3,5,	3,1,4,	3,4,5,	5,4,2
	};

	for (u32 i = 0; i < i_fromIdx.get_size() / 3; i++) {
		floral::vec3f v[6];
		v[0] = i_fromVtx[i_fromIdx[i * 3]];
		v[1] = i_fromVtx[i_fromIdx[i * 3 + 1]];
		v[2] = i_fromVtx[i_fromIdx[i * 3 + 2]];

		v[3] = floral::normalize((v[0] + v[1]) / 2.0f);
		v[4] = floral::normalize((v[1] + v[2]) / 2.0f);
		v[5] = floral::normalize((v[2] + v[0]) / 2.0f);

		for (u32 k = 0; k < 12; k++) {
			u32 index = o_toVtx.find(v[tmpIdx[k]], &compare_vec3f_point);
			if (index == o_toVtx.get_terminated_index()) {
				o_toVtx.push_back(v[tmpIdx[k]]);
				o_toIdx.push_back(o_toVtx.get_size() - 1);
			} else {
				o_toIdx.push_back(index);
			}
		}
	}
}


geo_generate_result_t generate_unit_icosphere_3d(const s32 i_startIdx, const size i_vtxStride, const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");

	static const floral::vec3f positions[12] =
	{
		floral::vec3f(-0.525731f, 0, 0.850651f), floral::vec3f(0.525731f, 0, 0.850651f),
		floral::vec3f(-0.525731f, 0, -0.850651f), floral::vec3f(0.525731f, 0, -0.850651f),
		floral::vec3f(0, 0.850651f, 0.525731f), floral::vec3f(0, 0.850651f, -0.525731f),
		floral::vec3f(0, -0.850651f, 0.525731f), floral::vec3f(0, -0.850651f, -0.525731f),
		floral::vec3f(0.850651f, 0.525731f, 0), floral::vec3f(-0.850651f, 0.525731f, 0),
		floral::vec3f(0.850651f, -0.525731f, 0), floral::vec3f(-0.850651f, -0.525731f, 0)
	};

	static const u32 indices[60] =
	{
		0,4,1,	0,9,4,	9,5,4,	4,5,8,	4,8,1,
		8,10,1,	8,3,10,	5,3,8,	5,2,3,	2,7,3,
		7,10,3,	7,6,10,	7,11,6,	11,0,6,	0,1,6,
		6,1,10,	9,0,11,	9,11,2,	9,2,5,	7,2,11
	};

	floral::inplace_array<floral::vec3f, 1024u> svBuff0;
	floral::inplace_array<floral::vec3f, 1024u> svBuff1;
	floral::inplace_array<u32, 4096u> siBuff0;
	floral::inplace_array<u32, 4096u> siBuff1;

	for (u32 i = 0; i < 12; i++)
	{
		svBuff0.push_back(positions[i]);
	}

	for (u32 i = 0; i < 60; i++)
	{
		siBuff0.push_back(indices[i]);
	}

	tesselate_icosphere(svBuff0, siBuff0, svBuff1, siBuff1);
	tesselate_icosphere(svBuff1, siBuff1, svBuff0, siBuff0);
	tesselate_icosphere(svBuff0, siBuff0, svBuff1, siBuff1);

	if (TEST_BIT(i_vtxFormat, (s32)geo_vertex_format_e::normal))
	{
		for (u32 i = 0; i < svBuff1.get_size(); i++)
		{
			vertex_pn_t* vtx = (vertex_pn_t*)o_vtxData;

			vtx->position = svBuff1[i];
			vtx->normal = floral::normalize(svBuff1[i]);

			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}
	}
	else
	{
		for (u32 i = 0; i < svBuff1.get_size(); i++)
		{
			floral::vec3f* pos = (floral::vec3f*)o_vtxData;
			*pos = svBuff1[i];
			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}
	}

	for (u32 i = 0; i < siBuff1.get_size() / 3; i++)
	{
		o_idxData[3 * i] = i_startIdx + siBuff1[i * 3 + 2];
		o_idxData[3 * i + 1] = i_startIdx + siBuff1[i * 3 + 1];
		o_idxData[3 * i + 2] = i_startIdx + siBuff1[i * 3];
	}

	geo_generate_result_t genResult;
	genResult.vertices_generated = svBuff1.get_size();
	genResult.indices_generated = siBuff1.get_size();
	return genResult;
}

//----------------------------------------------

manifold_geo_generate_result_t generate_manifold_quadtes_unit_plane_3d(
		const s32 i_startIdx, const size i_vtxStride,
		const s32 i_vtxFormat, const f32 i_quadSize, voidptr o_vtxData, s32* o_idxData,
		const s32 i_mnfStartIdx, const size i_mnfVtxStride, const f32 i_mnfThickness,
		const s32 i_mnfVtxFormat, voidptr o_mnfVtxData, s32* o_mnfIdxData)
{
	FLORAL_ASSERT_MSG(i_mnfThickness > 0.0f, "Manifold thickness must be greater than 0");

	manifold_geo_generate_result_t genResult;

	// generate the plane
	{
		geo_generate_result_t objResult = generate_quadtes_unit_plane_3d(i_startIdx, i_vtxStride, i_vtxFormat, i_quadSize, o_vtxData, o_idxData);

		apply_tranforms(i_vtxFormat, objResult.vertices_generated, i_vtxStride, o_vtxData);

		genResult.vertices_generated = objResult.vertices_generated;
		genResult.indices_generated = objResult.indices_generated;
	}

	// generate the manifold object
	{
		geo_generate_result_t manifoldResult = generate_unit_box_3d(i_mnfStartIdx, i_mnfVtxStride, i_mnfVtxFormat, o_mnfVtxData, o_mnfIdxData);

		aptr mnfVtxData = (aptr)o_mnfVtxData;
		for (size i = 0; i < manifoldResult.vertices_generated; i++)
		{
			floral::vec3f* pos = (floral::vec3f*)mnfVtxData;
			if (fabs(pos->y - 1.0f) < s_epsilon)
			{
				pos->y = 0.0f;
			}
			else if (fabs(pos->y + 1.0f) < s_epsilon)
			{
				pos->y = -i_mnfThickness;
			}

			mnfVtxData += i_mnfVtxStride;
		}

		apply_tranforms(i_mnfVtxFormat, manifoldResult.vertices_generated, i_mnfVtxStride, o_mnfVtxData);

		genResult.manifold_vertices_generated = manifoldResult.vertices_generated;
		genResult.manifold_indices_generated = manifoldResult.indices_generated;
	}

	return genResult;
}

manifold_geo_generate_result_t generate_manifold_unit_plane_3d(
		const s32 i_startIdx, const size i_vtxStride,
		const s32 i_vtxFormat, voidptr o_vtxData, s32* o_idxData,
		const s32 i_mnfStartIdx, const size i_mnfVtxStride, const f32 i_mnfThickness,
		const s32 i_mnfVtxFormat, voidptr o_mnfVtxData, s32* o_mnfIdxData)
{
	FLORAL_ASSERT_MSG(i_mnfThickness > 0.0f, "Manifold thickness must be greater than 0");

	manifold_geo_generate_result_t genResult;

	// generate the plane
	{
		geo_generate_result_t objResult = generate_unit_plane_3d(i_startIdx, i_vtxStride, i_vtxFormat, o_vtxData, o_idxData);

		apply_tranforms(i_vtxFormat, objResult.vertices_generated, i_vtxStride, o_vtxData);

		genResult.vertices_generated = objResult.vertices_generated;
		genResult.indices_generated = objResult.indices_generated;
	}

	// generate the manifold object
	{
		geo_generate_result_t manifoldResult = generate_unit_box_3d(i_mnfStartIdx, i_mnfVtxStride, i_mnfVtxFormat, o_mnfVtxData, o_mnfIdxData);

		aptr mnfVtxData = (aptr)o_mnfVtxData;
		for (size i = 0; i < manifoldResult.vertices_generated; i++)
		{
			floral::vec3f* pos = (floral::vec3f*)mnfVtxData;
			if (fabs(pos->y - 1.0f) < s_epsilon)
			{
				pos->y = 0.0f;
			}
			else if (fabs(pos->y + 1.0f) < s_epsilon)
			{
				pos->y = -i_mnfThickness;
			}

			mnfVtxData += i_mnfVtxStride;
		}

		apply_tranforms(i_mnfVtxFormat, manifoldResult.vertices_generated, i_mnfVtxStride, o_mnfVtxData);

		genResult.manifold_vertices_generated = manifoldResult.vertices_generated;
		genResult.manifold_indices_generated = manifoldResult.indices_generated;
	}

	return genResult;
}

}
