#include "floral/gpds/camera.h"

#include "floral/math/transform.h"
#include "floral/math/utils.h"

namespace floral
{
// ------------------------------------------------------------------

mat4x4f construct_lookat_dir_rh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtDir)
{
	mat4x4f m(1.0f);
	vec3f front = -normalize(lookAtDir);				// points out of the screen
	vec3f right = normalize(cross(upDir, front));		// points rightward
	vec3f up = cross(front, right);						// points upward

	m[0][0] = right.x;
	m[1][0] = right.y;
	m[2][0] = right.z;

	m[0][1] = up.x;
	m[1][1] = up.y;
	m[2][1] = up.z;

	m[0][2] = front.x;
	m[1][2] = front.y;
	m[2][2] = front.z;

	m[3][0] = -dot(right, camPos);
	m[3][1] = -dot(up, camPos);
	m[3][2] = -dot(front, camPos);

	return m;
}

// ------------------------------------------------------------------

mat4x4f construct_lookat_dir_lh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtDir)
{
	mat4x4f m(1.0f);
	vec3f front = normalize(lookAtDir);
	vec3f right = normalize(cross(upDir, front));
	vec3f up = cross(front, right);

	m[0][0] = right.x;
	m[1][0] = right.y;
	m[2][0] = right.z;

	m[0][1] = up.x;
	m[1][1] = up.y;
	m[2][1] = up.z;

	m[0][2] = front.x;
	m[1][2] = front.y;
	m[2][2] = front.z;

	m[3][0] = -dot(right, camPos);
	m[3][1] = -dot(up, camPos);
	m[3][2] = -dot(front, camPos);

	return m;
}

// ------------------------------------------------------------------

mat4x4f construct_lookat_point_rh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtPoint)
{
	vec3f lookAtDir = lookAtPoint - camPos;
	return construct_lookat_dir_rh(upDir, camPos, lookAtDir);
}

// ------------------------------------------------------------------

mat4x4f construct_lookat_point_lh(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtPoint)
{
	vec3f lookAtDir = lookAtPoint - camPos;
	return construct_lookat_dir_lh(upDir, camPos, lookAtDir);
}

// ------------------------------------------------------------------

mat4x4f construct_lookat_dir_rh(const camera_view_t& i_desc)
{
	return construct_lookat_dir_rh(i_desc.up_direction, i_desc.position, i_desc.look_at);
}

// ------------------------------------------------------------------

mat4x4f construct_lookat_dir_lh(const camera_view_t& i_desc)
{
	return construct_lookat_dir_lh(i_desc.up_direction, i_desc.position, i_desc.look_at);
}

// ------------------------------------------------------------------

mat4x4f construct_lookat_point_rh(const camera_view_t& i_desc)
{
	return construct_lookat_point_rh(i_desc.up_direction, i_desc.position, i_desc.look_at);
}

// ------------------------------------------------------------------

mat4x4f construct_lookat_point_lh(const camera_view_t& i_desc)
{
	return construct_lookat_point_lh(i_desc.up_direction, i_desc.position, i_desc.look_at);
}

// ------------------------------------------------------------------

mat4x4f construct_orthographic_rh(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far)
{
	mat4x4f m(1.0f);
	m[0][0] = 2.0f / (right - left);
	m[1][1] = 2.0f / (top - bottom);
	m[2][2] = -2.0f / (far - near);
	m[3][0] = - (right + left) / (right - left);
	m[3][1] = - (top + bottom) / (top - bottom);
	m[3][2] = - (far + near) / (far - near);
	return m;
}

// ------------------------------------------------------------------

mat4x4f construct_orthographic_lh(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far)
{
	mat4x4f m(1.0f);
	m[0][0] = 2.0f / (right - left);
	m[1][1] = 2.0f / (top - bottom);
	m[2][2] = 2.0f / (far - near);
	m[3][0] = - (right + left) / (right - left);
	m[3][1] = - (top + bottom) / (top - bottom);
	m[3][2] = - (far + near) / (far - near);
	return m;
}

// ------------------------------------------------------------------

mat4x4f construct_orthographic_rh(const camera_ortho_t& i_desc)
{
	return construct_orthographic_rh(i_desc.left, i_desc.right, i_desc.top, i_desc.bottom, i_desc.near_plane, i_desc.far_plane);
}

// ------------------------------------------------------------------

mat4x4f construct_orthographic_lh(const camera_ortho_t& i_desc)
{
	return construct_orthographic_lh(i_desc.left, i_desc.right, i_desc.top, i_desc.bottom, i_desc.near_plane, i_desc.far_plane);
}

// ------------------------------------------------------------------

mat4x4f construct_perspective_rh(const f32 i_near, const f32 i_far, const f32 i_fovy, const f32 i_aspectRatio)
{
	const f32 tanHalfFovY = tanf(floral::to_radians(i_fovy / 2.0f));

	floral::mat4x4f m;
	m[0][0] = 1.0f / (i_aspectRatio * tanHalfFovY);
	m[1][1] = 1.0f / tanHalfFovY;
	m[2][2] = -(i_far + i_near) / (i_far - i_near);
	m[2][3] = -1.0f;
	m[3][2] = -2.0f * i_far * i_near / (i_far - i_near);

	return m;
}

// ------------------------------------------------------------------

mat4x4f construct_perspective_lh(const f32 i_near, const f32 i_far, const f32 i_fovy, const f32 i_aspectRatio)
{
	const f32 tanHalfFovY = tanf(floral::to_radians(i_fovy / 2.0f));

	floral::mat4x4f m;
	m[0][0] = 1.0f / (i_aspectRatio * tanHalfFovY);
	m[1][1] = 1.0f / tanHalfFovY;
	m[2][2] = (i_far + i_near) / (i_far - i_near);
	m[2][3] = 1.0f;
	m[3][2] = -2.0f * i_far * i_near / (i_far - i_near);

	return m;
}

// ------------------------------------------------------------------

mat4x4f construct_perspective_rh(const camera_persp_t& i_desc)
{
	return construct_perspective_rh(i_desc.near_plane, i_desc.far_plane, i_desc.fov, i_desc.aspect_ratio);
}

// ------------------------------------------------------------------

mat4x4f construct_perspective_lh(const camera_persp_t& i_desc)
{
	return construct_perspective_lh(i_desc.near_plane, i_desc.far_plane, i_desc.fov, i_desc.aspect_ratio);
}

// ------------------------------------------------------------------
}
