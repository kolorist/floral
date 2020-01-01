#include "floral/gpds/camera.h"

#include "floral/math/transform.h"
#include "floral/math/utils.h"

namespace floral {

mat4x4f construct_lookat_dir(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtDir)
{
	mat4x4f tMat;
	tMat = construct_translation3d(-camPos);
	mat4x4f lMat(1.0f);
	vec3f lookAtDirNorm = -normalize(lookAtDir);
	vec3f rightDirNorm = normalize(cross(upDir, -lookAtDir));
	vec3f topDirNorm = normalize(cross(-lookAtDir, rightDirNorm));
	lMat[0][0] = rightDirNorm.x;	lMat[0][1] = topDirNorm.x;	lMat[0][2] = lookAtDirNorm.x;
	lMat[1][0] = rightDirNorm.y;	lMat[1][1] = topDirNorm.y;	lMat[1][2] = lookAtDirNorm.y;
	lMat[2][0] = rightDirNorm.z;	lMat[2][1] = topDirNorm.z;	lMat[2][2] = lookAtDirNorm.z;
	return (lMat * tMat);	// rotate first then translate the coordinate
}

mat4x4f construct_lookat_dir(const camera_view_t& i_desc)
{
	return construct_lookat_dir(i_desc.up_direction, i_desc.position, i_desc.look_at);
}

mat4x4f construct_lookat_point(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtPoint)
{
	vec3f lookAtDir = lookAtPoint - camPos;
	return construct_lookat_dir(upDir, camPos, lookAtDir);
}

mat4x4f construct_lookat_point(const camera_view_t& i_desc)
{
	vec3f dir = i_desc.look_at - i_desc.position;
	return construct_lookat_dir(i_desc.up_direction, i_desc.position, dir);
}

mat4x4f construct_orthographic(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far)
{
	mat4x4f pMat;
	pMat[0][0] = 2.0f / (right - left);		pMat[3][0] = - (right + left) / (right - left);
	pMat[1][1] = 2.0f / (top - bottom);		pMat[3][1] = - (top + bottom) / (top - bottom);
	pMat[2][2] = -2.0f / (far - near);		pMat[3][2] = - (far + near) / (far - near);
	pMat[3][3] = 1.0f;
	return pMat;
}

mat4x4f construct_orthographic(const camera_ortho_t& i_desc)
{
	return construct_orthographic(i_desc.left, i_desc.right, i_desc.top, i_desc.bottom, i_desc.near_plane, i_desc.far_plane);
}

// TODO: note that this is symetric view, where abs(left) == abs(right) and abs(top) == abs(bottom)
// we have to reduce the computation as much as posible to minimize floating point calculation errors
// NOTE: this fov value is horizontal field of view, normally renderer use vertical field of view but we
// will see what may happen with this kind of setup
mat4x4f construct_perspective(const f32 near, const f32 far, const f32 fov, const f32 aspectRatio)
{
	mat4x4f pMat;
	// near and far must be positive (distance to the view point)
	f32 fovRad = to_radians(fov);
	f32 tanHalfFov = tanf(fovRad / 2.0f);
	pMat[0][0] = 1.0f / tanHalfFov;
	pMat[1][1] = aspectRatio / tanHalfFov;
	pMat[2][2] = - (far + near) / (far - near);
	pMat[3][2] = - (2.0f * near * far) / (far - near);
	pMat[2][3] = -1.0f;

	return pMat;
}

mat4x4f construct_perspective(const camera_persp_t& i_desc)
{
	return construct_perspective(i_desc.near_plane, i_desc.far_plane, i_desc.fov, i_desc.aspect_ratio);
}

}
