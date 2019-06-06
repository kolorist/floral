#include "floral/comgeo/shapegen.h"

#include "floral/gpds/vec.h"

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

geo_generate_result_t generate_unit_box_3d(const s32 i_startIdx, const size i_vtxStride, voidptr o_vtxData, s32* o_idxData)
{
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

	for (size i = 0; i < 36; i++)
	{
		o_idxData[i] = i_startIdx + indices[i];
		floral::vec3f* vtx = (floral::vec3f*)o_vtxData;
		*vtx = vertices[i];
		o_vtxData = (voidptr)((aptr)o_vtxData + i_vtxStride);
	}

	geo_generate_result_t genResult;
	genResult.vertices_generated = 8;
	genResult.indices_generated = 36;
	return genResult;
}

}
