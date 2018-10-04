#include "math/coordinate.h"

#include <math.h>

#include "stdaliases.h"

namespace floral {

#define CP_UDIR     0
#define CP_VDIR     1
#define CP_FACEAXIS 2

floral::vec3f sgFace2DMapping[6][3] = {
	//XPOS face
	{floral::vec3f( 0,  0, 1),   //u towards positive Z
	 floral::vec3f( 0, 1,  0),   //v towards positive Y
	 floral::vec3f(1,  0,  0)},  //pos X axis  
	//XNEG face
	{floral::vec3f(0,  0,  -1),   //u towards negative Z
	 floral::vec3f(0, 1,  0),   //v towards positive Y
	 floral::vec3f(-1,  0,  0)},  //neg X axis       
	//YPOS face
	{floral::vec3f(1, 0, 0),     //u towards positive X
	 floral::vec3f(0, 0, 1),     //v towards positive Z
	 floral::vec3f(0, 1 , 0)},   //pos Y axis  
	//YNEG face
	{floral::vec3f(1, 0, 0),     //u towards positive X
	 floral::vec3f(0, 0 , -1),   //v towards negative Z
	 floral::vec3f(0, -1 , 0)},  //neg Y axis  
	//ZPOS face
	{floral::vec3f(-1, 0, 0),     //u towards negative X
	 floral::vec3f(0, 1, 0),    //v towards positive Y
	 floral::vec3f(0, 0,  1)},   //pos Z axis  
	//ZNEG face
	{floral::vec3f(1, 0, 0),    //u towards positive X
	 floral::vec3f(0, 1, 0),    //v towards positive Y
	 floral::vec3f(0, 0, -1)},   //neg Z axis  
};

//----------------------------------------------
floral::vec3f texel_coord_to_cube_coord(const s32 i_faceIdx, const f32 i_u, const f32 i_v, const s32 i_size)
{
	floral::vec2f nvcUV;
	floral::vec3f tempVec;
	
	floral::vec3f retDir(0.0f, 0.0f, 0.0f);
	// TODO: another type cast for f32?
	nvcUV.x = (2.0f * ((f32)i_u + 0.5f) / (f32)i_size) - 1.0f;
	nvcUV.y = (2.0f * ((f32)i_v + 0.5f) / (f32)i_size) - 1.0f;
	
	// Code from Nvtt : http://code.google.com/p/nvidia-texture-tools/source/browse/trunk/src/nvtt/CubeSurface.cpp
	f32 a = powf(f32(i_size), 2.0f) / powf(f32(i_size - 1), 3.0f);
	nvcUV.x = a * powf(nvcUV.x, 3) + nvcUV.x;
	nvcUV.y = a * powf(nvcUV.y, 3) + nvcUV.y;

	// Get current vector
	//generate x,y,z vector (xform 2d NVC coord to 3D vector)
	//U contribution
	retDir = sgFace2DMapping[i_faceIdx][CP_UDIR] * nvcUV.x;
	//V contribution
	tempVec = sgFace2DMapping[i_faceIdx][CP_VDIR] * nvcUV.y;
	retDir = tempVec + retDir;
	//add face axis
	retDir = sgFace2DMapping[i_faceIdx][CP_FACEAXIS] + retDir;
	//normalize vector
	return retDir.normalize();
}

//----------------------------------------------
static f32 get_area_element(f32 x, f32 y)
{
	return atan2f(x * y, sqrtf(x * x + y * y + 1));
}

f32 texel_coord_to_solid_angle(const s32 i_faceIdx, const f32 i_u, const f32 i_v, const s32 i_size)
{
	// transform from [0..res - 1] to [- (1 - 1 / res) .. (1 - 1 / res)]
	// (+ 0.5f is for texel center addressing)
	f32 U = (2.0f * ((f32)i_u + 0.5f) / (f32)i_size ) - 1.0f;
	f32 V = (2.0f * ((f32)i_v + 0.5f) / (f32)i_size ) - 1.0f;

	// Shift from a demi texel, mean 1.0f / i_size with U and V in [-1..1]
	f32 invRes = 1.0f / i_size;

	// U and V are the -1..1 texture coordinate on the current face.
	// Get projected area for this texel
	f32 x0 = U - invRes;
	f32 y0 = V - invRes;
	f32 x1 = U + invRes;
	f32 y1 = V + invRes;
	f32 solidAngle = get_area_element(x0, y0) - get_area_element(x0, y1) - get_area_element(x1, y0) + get_area_element(x1, y1);

	return solidAngle;
}
	
}