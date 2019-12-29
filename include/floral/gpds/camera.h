#pragma once

#include "floral/stdaliases.h"

#include "vec.h"
#include "mat.h"

namespace floral
{

struct camera_view_t
{
	vec3f										position;
	vec3f										look_at; // maybe direction or target location
	vec3f										up_direction;
};

struct camera_ortho_t
{
	f32											left, right, top, bottom;
	f32											near_plane, far_plane;
};

struct camera_persp_t
{
	f32											near_plane, far_plane;
	f32											fov;
	f32											aspect_ratio;
};

// view matrix construction
mat4x4f construct_lookat_dir(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtDir);
mat4x4f construct_lookat_dir(const camera_view_t& i_desc);
mat4x4f construct_lookat_point(const camera_view_t& i_desc);

#ifndef construct_lookat
#define construct_lookat construct_lookat_dir
#endif

// projection matrix construction
mat4x4f construct_orthographic(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far);
mat4x4f construct_orthographic(const camera_ortho_t& i_desc);
// fov (degrees)
// near and far must be positive
mat4x4f construct_perspective(const f32 near, const f32 far, const f32 fov, const f32 aspectRatio);
mat4x4f construct_perspective(const camera_persp_t& i_desc);

}
