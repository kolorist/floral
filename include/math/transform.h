#ifndef __FLORAL_TRANSFORM_H__
#define __FLORAL_TRANSFORM_H__

#include <stdaliases.h>

#include <gpds/vec.h>
#include <gpds/mat.h>

namespace floral {
	mat4x4f construct_translation3d(f32 deltaX, f32 deltaY, f32 deltaZ);
	mat4x4f construct_scaling3d(f32 scaleX, f32 scaleY, f32 scaleZ);
	mat4x4f construct_Xrotation3d(f32 rX);
	mat4x4f construct_Yrotation3d(f32 rY);
	mat4x4f cosntruct_Zrotation3d(f32 rZ);
}

#endif // __FLORAL_TRANSFORM_H__
