#include "math/transform.h"

#include <math/utils.h>

#include <math.h>

namespace floral {
	mat4x4f construct_translation3d(f32 deltaX, f32 deltaY, f32 deltaZ)
	{
		mat4x4f tMat = mat4x4f(1.0f);
		tMat[3][0] = deltaX;
		tMat[3][1] = deltaY;
		tMat[3][2] = deltaZ;
		// TODO: move sematic?
		return tMat;
	}

	mat4x4f construct_translation3d(const vec3f& delta)
	{
		mat4x4f tMat = mat4x4f(1.0f);
		tMat[3][0] = delta.x;
		tMat[3][1] = delta.y;
		tMat[3][2] = delta.z;
		// TODO: move sematic?
		return tMat;
	}

	mat4x4f construct_scaling3d(f32 scaleX, f32 scaleY, f32 scaleZ)
	{
		mat4x4f tMat;
		tMat[0][0] = scaleX;
		tMat[1][1] = scaleY;
		tMat[2][2] = scaleZ;
		tMat[3][3] = 1.0f;
		return tMat;
	}

	mat4x4f construct_scaling3d(const vec3f& scale)
	{
		mat4x4f tMat;
		tMat[0][0] = scale.x;
		tMat[1][1] = scale.y;
		tMat[2][2] = scale.z;
		tMat[3][3] = 1.0f;
		return tMat;
	}

	mat4x4f construct_Xrotation3d(f32 rX)
	{
		mat4x4f tMat;
		tMat[0][0] = 1.0f;
		tMat[1][1] = cosf(rX);
		tMat[1][2] = -sinf(rX);
		tMat[2][1] = sinf(rX);
		tMat[2][2] = cosf(rX);
		tMat[3][3] = 1.0f;
		return tMat;
	}

	mat4x4f construct_Yrotation3d(f32 rY)
	{
		mat4x4f tMat;
		tMat[0][0] = cosf(rY);
		tMat[0][2] = sinf(rY);
		tMat[1][1] = 1.0f;
		tMat[2][0] = -sinf(rY);
		tMat[2][2] = cosf(rY);
		tMat[3][3] = 1.0f;
		return tMat;
	}

	mat4x4f construct_Zrotation3d(f32 rZ)
	{
		mat4x4f tMat;
		tMat[0][0] = cosf(rZ);
		tMat[0][1] = -sinf(rZ);
		tMat[1][0] = sinf(rZ);
		tMat[1][1] = cosf(rZ);
		tMat[2][2] = 1.0f;
		tMat[3][3] = 1.0f;
		return tMat;
	}

	mat4x4f construct_invert(const mat4x4f& m)
	{
		mat4x4f tMat;
		return tMat;
	}

	mat3x3f construct_invert(const mat3x3f& m)
	{
		mat3x3f tMat;
		return tMat;
	}

	mat4x4f construct_transpose(const mat4x4f& m)
	{
		mat4x4f tMat;
		tMat[0][0] = m[0][0]; tMat[0][1] = m[1][0]; tMat[0][2] = m[2][0]; tMat[0][3] = m[3][0];
		tMat[1][0] = m[0][1]; tMat[1][1] = m[1][1]; tMat[1][2] = m[2][1]; tMat[1][3] = m[3][1];
		tMat[2][0] = m[0][2]; tMat[2][1] = m[1][2]; tMat[2][2] = m[2][2]; tMat[2][3] = m[3][2];
		tMat[3][0] = m[0][3]; tMat[3][1] = m[1][3]; tMat[3][2] = m[2][3]; tMat[3][3] = m[3][3];
		return tMat;
	}

	mat3x3f construct_transpose(const mat3x3f& m)
	{
		mat3x3f tMat;
		tMat[0][0] = m[0][0]; tMat[0][1] = m[1][0]; tMat[0][2] = m[2][0];
		tMat[1][0] = m[0][1]; tMat[1][1] = m[1][1]; tMat[1][2] = m[2][1];
		tMat[2][0] = m[0][2]; tMat[2][1] = m[1][2]; tMat[2][2] = m[2][2];
		return tMat;
	}

	mat4x4f construct_lookat(const vec3f& upDir, const vec3f& camPos, const vec3f& lookAtDir)
	{
		mat4x4f lMat;
		vec3f rightDir = vec3f::cross(upDir, lookAtDir);
		lMat[0][0] = rightDir.x;	lMat[0][1] = upDir.x;	lMat[0][2] = lookAtDir.x;
		lMat[1][0] = rightDir.y;	lMat[1][1] = upDir.y;	lMat[1][2] = lookAtDir.y;
		lMat[2][0] = rightDir.z;	lMat[2][1] = upDir.z;	lMat[2][2] = lookAtDir.z;
		lMat[3][0] = camPos.x;		lMat[3][1] = camPos.y;	lMat[3][2] = camPos.z;
		return lMat;
	}

	mat4x4f construct_orthographic(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far)
	{
		mat4x4f pMat;
		pMat[0][0] = 2.0f / (right - left);		pMat[0][3] = (right + left) / 2.0f;
		pMat[1][1] = 2.0f / (top - bottom);		pMat[1][3] = (top + bottom) / 2.0f;
		pMat[2][2] = -2.0f / (far - near);		pMat[2][3] = -(far + near) / 2.0f;
		pMat[3][3] = 1.0f;
		return pMat;
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
		f32 right = near * tanHalfFov;
		f32 left = -right;
		f32 top = right / aspectRatio;
		f32 bottom = -top;
		pMat[0][0] = 2.0f * near / (right - left);	pMat[0][2] = (right + left) / (right - left);
		pMat[1][1] = 2.0f * near / (top - bottom);	pMat[1][2] = (top + bottom) / (top - bottom);
		pMat[2][2] = - (far + near) / (far - near);	pMat[2][3] = - (2.0f * near * far) / (far - near);
		pMat[3][2] = -1.0f;

		return pMat;
	}
}
