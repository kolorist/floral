#include "floral/comgeo/shapegen.h"

#include "floral/math/utils.h"
#include "floral/assert/assert.h"
#include "floral/gpds/vec.h"
#include "floral/containers/array.h"

#include <algorithm>

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

void apply_tranforms(const geo_vertex_format_e i_vtxFormat, const u32 i_vtxCount, const size i_vtxStride, voidptr io_vtxData)
{
	if (s_topXForm == 0)
	{
		return;
	}

	floral::mat4x4f m(1.0f);

	for (size i = 0; i < s_topXForm; i++)
	{
		m = s_xformStack[i] *  m;
	}

	aptr vtxData = (aptr)io_vtxData;

	if (TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal))
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

void apply_tranforms(floral::vec4f& io_vec)
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

	io_vec = m * io_vec;
}

//----------------------------------------------

geo_generate_result_t generate_quadtes_plane_3d(
		const s32 i_startIdx, const size i_vtxStride, const geo_vertex_format_e i_vtxFormat,
		const f32 i_quadSize, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");

	vertex_pn_t vertices[] =
	{
		floral::vec3f(1.0f, 0.0f, 1.0f),		floral::vec3f(0.0f, 1.0f, 0.0f),
		floral::vec3f(1.0f, 0.0f, -1.0f),		floral::vec3f(0.0f, 1.0f, 0.0f),
		floral::vec3f(-1.0f, 0.0f, -1.0f),		floral::vec3f(0.0f, 1.0f, 0.0f),
		floral::vec3f(-1.0f, 0.0f, 1.0f),		floral::vec3f(0.0f, 1.0f, 0.0f)
	};

	apply_tranforms(i_vtxFormat, 4, sizeof(vertex_pn_t), vertices);
	const f32 gridSize = i_quadSize;
	const f32 edgeLengthX = floral::length(vertices[3].position - vertices[0].position);
	const f32 edgeLengthZ = floral::length(vertices[1].position - vertices[0].position);
	const s32 gridPerEdgeX = (s32)(edgeLengthX / gridSize) + 1;
	const s32 gridPerEdgeZ = (s32)(edgeLengthZ / gridSize) + 1;
	const floral::vec3f ex = vertices[3].position - vertices[0].position;
	const floral::vec3f ez = vertices[1].position - vertices[0].position;
	const floral::vec3f dx = floral::normalize(vertices[3].position - vertices[0].position) * gridSize;
	const floral::vec3f dz = floral::normalize(vertices[1].position - vertices[0].position) * gridSize;

	floral::inplace_array<floral::vec3f, 1024u> vertexArray;
	floral::inplace_array<s32, 4096u> indexArray;

	static const s32 indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	for (s32 i = 0; i < gridPerEdgeX; i++)
	{
		for (s32 j = 0; j < gridPerEdgeZ; j++)
		{
			floral::vec3f v[4];

			floral::vec3f dxMax = (i + 1 == gridPerEdgeX) ? ex : dx * (f32)(i + 1);
			floral::vec3f dzMax = (j + 1 == gridPerEdgeZ) ? ez : dz * (f32)(j + 1);

			v[0] = vertices[0].position + dx * (f32)i + dz * (f32)j;
			v[1] = vertices[0].position + dx * (f32)i + dzMax;
			v[2] = vertices[0].position + dxMax + dzMax;
			v[3] = vertices[0].position + dxMax + dz * (f32)j;

			for (u32 k = 0; k < 6; k++)
			{
				ssize index = vertexArray.find(v[indices[k]], &compare_vec3f_point);
				if (index == vertexArray.get_terminated_index())
				{
					vertexArray.push_back(v[indices[k]]);
					indexArray.push_back(s32(vertexArray.get_size() - 1));
				}
				else
				{
					indexArray.push_back((s32)index);
				}
			}
		}
	}

	if (TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal))
	{
		for (u32 i = 0; i < vertexArray.get_size(); i++)
		{
			vertex_pn_t* vtx = (vertex_pn_t*)o_vtxData;
			vtx->position = vertexArray[i];
			vtx->normal = vertices[0].normal;
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
	genResult.vertices_generated = (u32)vertexArray.get_size();
	genResult.indices_generated = (u32)indexArray.get_size();
	return genResult;
}

//----------------------------------------------

geo_generate_result_t create_unit_plane_3d(const s32 i_startIdx, const size i_vtxStride, const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");

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

	if (TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal))
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

geo_generate_result_t generate_unit_box_3d_no_normals(const s32 i_startIdx, const size i_vtxStride, const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");
	FLORAL_ASSERT(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal) == 0);

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

geo_generate_result_t generate_unit_box_3d_with_normals(const s32 i_startIdx, const size i_vtxStride, const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");
	FLORAL_ASSERT_MSG(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal) != 0, "Vertex format must contain normal semantic");
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

			const ssize oldIdx = vertexArray.find(vtx, &compare_vertex_pn);
			if (oldIdx == vertexArray.get_terminated_index())
			{
				vertexArray.push_back(vtx);
				indexArray.push_back(s32(vertexArray.get_size() - 1));
			}
			else
			{
				indexArray.push_back((s32)oldIdx);
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
	genResult.vertices_generated = (u32)vertexArray.get_size();
	genResult.indices_generated = (u32)indexArray.get_size();
	return genResult;
}

geo_generate_result_t generate_unit_box_3d(const s32 i_startIdx, const size i_vtxStride, const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	if (TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal))
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
			ssize index = o_toVtx.find(v[tmpIdx[k]], &compare_vec3f_point);
			if (index == o_toVtx.get_terminated_index()) {
				o_toVtx.push_back(v[tmpIdx[k]]);
				o_toIdx.push_back(u32(o_toVtx.get_size() - 1));
			} else {
				o_toIdx.push_back((u32)index);
			}
		}
	}
}


geo_generate_result_t generate_unit_icosphere_3d(const u32 i_tesLevel, const s32 i_startIdx, const size i_vtxStride, const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");

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

	floral::inplace_array<floral::vec3f, 1024u>* frontSvBuff = &svBuff0;
	floral::inplace_array<floral::vec3f, 1024u>* backSvBuff = &svBuff1;
	floral::inplace_array<u32, 4096u>* frontSiBuff = &siBuff0;
	floral::inplace_array<u32, 4096u>* backSiBuff = &siBuff1;

	for (u32 i = 0; i < 12; i++)
	{
		backSvBuff->push_back(positions[i]);
	}

	for (u32 i = 0; i < 60; i++)
	{
		backSiBuff->push_back(indices[i]);
	}

	for (u32 i = 0; i < i_tesLevel; i++)
	{
		tesselate_icosphere(*backSvBuff, *backSiBuff, *frontSvBuff, *frontSiBuff);
		if (i != i_tesLevel - 1)
		{
			std::swap(backSvBuff, frontSvBuff);
			std::swap(backSiBuff, frontSiBuff);
		}
	}

	if (TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal))
	{
		for (u32 i = 0; i < frontSvBuff->get_size(); i++)
		{
			vertex_pn_t* vtx = (vertex_pn_t*)o_vtxData;

			vtx->position = (*frontSvBuff)[i];
			vtx->normal = floral::normalize((*frontSvBuff)[i]);

			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}
	}
	else
	{
		for (u32 i = 0; i < frontSvBuff->get_size(); i++)
		{
			floral::vec3f* pos = (floral::vec3f*)o_vtxData;
			*pos = (*frontSvBuff)[i];
			o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
		}
	}

	for (u32 i = 0; i < frontSiBuff->get_size() / 3; i++)
	{
		o_idxData[3 * i] = i_startIdx + (*frontSiBuff)[i * 3 + 2];
		o_idxData[3 * i + 1] = i_startIdx + (*frontSiBuff)[i * 3 + 1];
		o_idxData[3 * i + 2] = i_startIdx + (*frontSiBuff)[i * 3];
	}

	geo_generate_result_t genResult;
	genResult.vertices_generated = (u32)frontSvBuff->get_size();
	genResult.indices_generated = (u32)frontSiBuff->get_size();
	return genResult;
}

geo_generate_result_t generate_unit_uvsphere_3d(
		const u32 i_startIdx, const size i_vtxStride,
		const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	FLORAL_ASSERT_MSG(TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::position) != 0, "Vertex format must contain position semantic");

	const size k_LongSegments = 32;
	const size k_LatSegments = 32;

	geo_generate_result_t genResult;
	genResult.indices_generated = 0;
	genResult.vertices_generated = 0;

	aptr vtxData = (aptr)o_vtxData;
	aptr offset = 0;
	floral::vec3f* iPos = (floral::vec3f*)vtxData;
	offset += sizeof(floral::vec3f);

	const bool hasNormal = (TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::normal));
	floral::vec3f* iNormal = nullptr;
	if (hasNormal)
	{
		iNormal = (floral::vec3f*)(vtxData + offset);
		offset += sizeof(floral::vec3f);
	}

	const bool hasUV = (TEST_BIT((s32)i_vtxFormat, (s32)geo_vertex_format_e::tex_coord));
	floral::vec2f* iUV = nullptr;
	if (hasUV)
	{
		iUV = (floral::vec2f*)(vtxData + offset);
		offset += sizeof(floral::vec2f);
	}

	for (size y = 0; y <= k_LatSegments; y++)
	{
		for (size x = 0; x <= k_LongSegments; x++)
		{
			f32 longSeg = (f32)x / (f32)k_LongSegments;
			f32 latSeg = (f32)y / (f32)k_LatSegments;

			floral::vec3f p(0.0f, 0.0f, 0.0f);
			p.x = cosf(longSeg * 2.0f * floral::pi) * sinf(latSeg * floral::pi);
			p.y = cosf(latSeg * floral::pi);
			p.z = sinf(longSeg * 2.0f * floral::pi) * sinf(latSeg * floral::pi);

			*iPos = p;
			iPos = (floral::vec3f*)((aptr)iPos + i_vtxStride);
			if (hasNormal)
			{
				*iNormal = p;
				iNormal = (floral::vec3f*)((aptr)iNormal + i_vtxStride);
			}
			if (hasUV)
			{
				*iUV = floral::vec2f(longSeg, latSeg);
				iUV = (floral::vec2f*)((aptr)iUV + i_vtxStride);
			}
		}
	}
	genResult.vertices_generated = (k_LongSegments + 1) * (k_LatSegments + 1);

#if 0
	// generate triangle strip
	bool oddRow = false;
	s32* idxData = o_idxData;
	for (int y = 0; y < k_LatSegments; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (int x = 0; x <= k_LongSegments; ++x)
			{
				*idxData = (y       * (k_LongSegments + 1) + x); idxData++;
				*idxData = ((y + 1) * (k_LongSegments + 1) + x); idxData++;
				genResult.indices_generated += 2;
			}
		}
		else
		{
			for (int x = k_LongSegments; x >= 0; --x)
			{
				*idxData = ((y + 1) * (k_LongSegments + 1) + x); idxData++;
				*idxData = (y       * (k_LongSegments + 1) + x); idxData++;
				genResult.indices_generated += 2;
			}
		}
		oddRow = !oddRow;
	}
#else
	s32* idxData = o_idxData;
	s32 k1, k2;
	for (s32 i = 0; i < k_LatSegments; i++)
	{
		k1 = i * (k_LongSegments + 1);
		k2 = k1 + k_LongSegments + 1;
		for (s32 j = 0; j <= k_LongSegments; j++, k1++, k2++)
		{
			if (i != 0)
			{
				*idxData = k1 + 1; idxData++;
				*idxData = k2; idxData++;
				*idxData = k1; idxData++;
				genResult.indices_generated += 3;
			}

			if (i != (k_LatSegments - 1))
			{
				*idxData = k2 + 1; idxData++;
				*idxData = k2; idxData++;
				*idxData = k1 + 1; idxData++;
				genResult.indices_generated += 3;
			}
		}
	}
#endif

	return genResult;
}

//----------------------------------------------

geo_generate_result_t generate_unit_plane_3d(
		const s32 i_startIdx, const size i_vtxStride,
		const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData)
{
	geo_generate_result_t objResult = create_unit_plane_3d(i_startIdx, i_vtxStride, i_vtxFormat, o_vtxData, o_idxData);

	apply_tranforms(i_vtxFormat, objResult.vertices_generated, i_vtxStride, o_vtxData);

	return objResult;
}

manifold_geo_generate_result_t generate_manifold_quadtes_unit_plane_3d(
		const s32 i_startIdx, const size i_vtxStride,
		const geo_vertex_format_e i_vtxFormat, const f32 i_quadSize, voidptr o_vtxData, s32* o_idxData,
		const s32 i_mnfStartIdx, const size i_mnfVtxStride, const f32 i_mnfThickness,
		const geo_vertex_format_e i_mnfVtxFormat, voidptr o_mnfVtxData, s32* o_mnfIdxData)
{
	FLORAL_ASSERT_MSG(i_mnfThickness > 0.0f, "Manifold thickness must be greater than 0");

	manifold_geo_generate_result_t genResult;

	// generate the plane
	{
		geo_generate_result_t objResult = generate_quadtes_plane_3d(
				i_startIdx, i_vtxStride, i_vtxFormat,
				i_quadSize, o_vtxData, o_idxData);

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
			if (pos->x > 0.0f)
				pos->x += i_mnfThickness;
			else
				pos->x -= i_mnfThickness;

			if (pos->z > 0.0f)
				pos->z += i_mnfThickness;
			else
				pos->z -= i_mnfThickness;

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
		const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData,
		const s32 i_mnfStartIdx, const size i_mnfVtxStride, const f32 i_mnfThickness,
		const geo_vertex_format_e i_mnfVtxFormat, voidptr o_mnfVtxData, s32* o_mnfIdxData)
{
	FLORAL_ASSERT_MSG(i_mnfThickness > 0.0f, "Manifold thickness must be greater than 0");

	manifold_geo_generate_result_t genResult;

	// generate the plane
	{
		geo_generate_result_t objResult = create_unit_plane_3d(i_startIdx, i_vtxStride, i_vtxFormat, o_vtxData, o_idxData);

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

manifold_geo_generate_result_t generate_manifold_icosphere_3d(
		const s32 i_startIdx, const size i_vtxStride,
		const geo_vertex_format_e i_vtxFormat, voidptr o_vtxData, s32* o_idxData,
		const s32 i_mnfStartIdx, const size i_mnfVtxStride, const f32 i_mnfThickness,
		const geo_vertex_format_e i_mnfVtxFormat, voidptr o_mnfVtxData, s32* o_mnfIdxData)
{
	FLORAL_ASSERT_MSG(i_mnfThickness > 0.0f, "Manifold thickness must be greater than 0");
	manifold_geo_generate_result_t genResult;

	{
		geo_generate_result_t objResult = generate_unit_icosphere_3d(3, i_startIdx, i_vtxStride, i_vtxFormat, o_vtxData, o_idxData);

		apply_tranforms(i_vtxFormat, objResult.vertices_generated, i_vtxStride, o_vtxData);

		genResult.vertices_generated = objResult.vertices_generated;
		genResult.indices_generated = objResult.indices_generated;
	}

	{
		geo_generate_result_t objResult = generate_unit_icosphere_3d(3, i_mnfStartIdx, i_mnfVtxStride, i_mnfVtxFormat, o_mnfVtxData, o_mnfIdxData);

		apply_tranforms(i_mnfVtxFormat, objResult.vertices_generated, i_mnfVtxStride, o_mnfVtxData);

		genResult.manifold_vertices_generated = objResult.vertices_generated;
		genResult.manifold_indices_generated = objResult.indices_generated;
	}

	return genResult;
}

}
