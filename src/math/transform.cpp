#include "math/transform.h"

#include <math.h>

namespace floral {
	mat4x4f construct_translation3d(f32 deltaX, f32 deltaY, f32 deltaZ)
	{
		mat4x4f tMat = mat4x4f(1.0f);
		tMat[0][3] = deltaX;
		tMat[1][3] = deltaY;
		tMat[2][3] = deltaZ;
		// TODO: move sematic?
		return tMat;
	}

	mat4x4f construct_translation3d(const vec3f& delta)
	{
		mat4x4f tMat = mat4x4f(1.0f);
		tMat[0][3] = delta.x;
		tMat[1][3] = delta.y;
		tMat[2][3] = delta.z;
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
}
