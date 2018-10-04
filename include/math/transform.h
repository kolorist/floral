#ifndef __FLORAL_TRANSFORM_H__
#define __FLORAL_TRANSFORM_H__

#include <stdaliases.h>

#include <gpds/vec.h>
#include <gpds/mat.h>

namespace floral {
	mat4x4f construct_translation3d(f32 deltaX, f32 deltaY, f32 deltaZ);
	mat4x4f construct_translation3d(const vec3f& delta);
	mat4x4f construct_scaling3d(f32 scaleX, f32 scaleY, f32 scaleZ);
	mat4x4f construct_scaling3d(const vec3f& scale);
	// in radians
	mat4x4f construct_Xrotation3d(f32 rX);
	// in radians
	mat4x4f construct_Yrotation3d(f32 rY);
	// in radians
	mat4x4f construct_Zrotation3d(f32 rZ);
	// in radians
	mat4x4f construct_axis_rotation3d(const vec3f& axis, const f32 angle);
	mat4x4f construct_invert(const mat4x4f& m);
	mat3x3f construct_invert(const mat3x3f& m);
	mat4x4f construct_transpose(const mat4x4f& m);
	mat3x3f construct_transpose(const mat3x3f& m);

}

#endif // __FLORAL_TRANSFORM_H__
