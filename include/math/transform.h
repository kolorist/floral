#pragma once

#include <stdaliases.h>

#include <gpds/vec.h>
#include <gpds/mat.h>
#include <gpds/quaternion.h>

namespace floral {

mat4x4f construct_translation3d(const f32 i_deltaX, const f32 i_deltaY, const f32 i_deltaZ);
mat4x4f construct_translation3d(const vec3f& i_delta);

mat4x4f construct_scaling3d(const f32 i_scaleX, const f32 i_scaleY, const f32 i_scaleZ);
mat4x4f construct_scaling3d(const vec3f& i_scale);

// in radians
mat4x4f construct_Xrotation3d(const f32 i_rX);
// in radians
mat4x4f construct_Yrotation3d(const f32 i_rY);
// in radians
mat4x4f construct_Zrotation3d(const f32 i_rZ);
// in radians
mat4x4f construct_axis_rotation3d(const vec3f& i_axis, const f32 i_angle);

// in degrees, positive direction: counter-clockwise
quaternionf construct_quaternion_euler(const vec3f& i_r);
quaternionf construct_quaternion_euler(const f32 i_rx, const f32 i_ry, const f32 i_rz);
quaternionf construct_quaternion_axis(const vec3f& i_axis, const f32 i_r);

mat4x4f construct_invert(const mat4x4f& i_m);
mat3x3f construct_invert(const mat3x3f& i_m);

mat4x4f construct_transpose(const mat4x4f& i_m);
mat3x3f construct_transpose(const mat3x3f& i_m);

}
