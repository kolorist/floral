#pragma once

#include "floral/stdaliases.h"

#include "vec.h"
#include "mat.h"

namespace floral
{
// ------------------------------------------------------------------

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

// ------------------------------------------------------------------

// view matrix construction
mat4x4f construct_lookat_dir_rh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtDir);
mat4x4f construct_lookat_dir_lh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtDir);
mat4x4f construct_lookat_point_rh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtPoint);
mat4x4f construct_lookat_point_lh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtPoint);
mat4x4f construct_lookat_dir_rh(const camera_view_t& i_desc);
mat4x4f construct_lookat_dir_lh(const camera_view_t& i_desc);
mat4x4f construct_lookat_point_rh(const camera_view_t& i_desc);
mat4x4f construct_lookat_point_lh(const camera_view_t& i_desc);

#ifndef construct_lookat_dir
#define construct_lookat_dir					construct_lookat_dir_rh
#endif

#ifndef construct_lookat_point
#define construct_lookat_point					construct_lookat_point_rh
#endif

#ifndef construct_lookat
#define construct_lookat						construct_lookat_point
#endif

// projection matrix construction
mat4x4f construct_orthographic_rh(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far);
mat4x4f construct_orthographic_lh(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far);
mat4x4f construct_orthographic_rh(const camera_ortho_t& i_desc);
mat4x4f construct_orthographic_lh(const camera_ortho_t& i_desc);

// fovy (degrees)
// near and far must be positive
mat4x4f construct_perspective_rh(const f32 i_near, const f32 i_far, const f32 i_fovy, const f32 i_aspectRatio);
mat4x4f construct_perspective_lh(const f32 i_near, const f32 i_far, const f32 i_fovy, const f32 i_aspectRatio);
mat4x4f construct_perspective_rh(const camera_persp_t& i_desc);
mat4x4f construct_perspective_lh(const camera_persp_t& i_desc);

#ifndef construct_orthographic
#define construct_orthographic					construct_orthographic_rh
#endif

#ifndef construct_perspective
#define construct_perspective					construct_perspective_rh
#endif

// ------------------------------------------------------------------
}
