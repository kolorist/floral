#include "math/transform.h"

#include <math/utils.h>

#include <math.h>

// way of matrix - vector multiplication
// opengl:
// 	a b c d			x			ax + by + cz + dw
// 	e f g h	  mul	y	equal	ex + fy + gz + hw
// 	i j k l			z			ix + jy + kz + lw
// 	m n o p			w			mx + ny + oz + pw
//
// cpu:
// 	a e i m
// 	b f j n
// 	c g k o
// 	d h l p

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

mat4x4f construct_axis_rotation3d(const vec3f& axis, const f32 angle)
{
	mat4x4f tMat;
	f32 c = cosf(angle);
	f32 s = sinf(angle);

	vec3f ax = normalize(axis);

	tMat[0][0] = c + (1 - c)      * ax.x     * ax.x;
	tMat[0][1] = (1 - c) * ax.x * ax.y + s * ax.z;
	tMat[0][2] = (1 - c) * ax.x * ax.z - s * ax.y;
	tMat[0][3] = 0;

	tMat[1][0] = (1 - c) * ax.y * ax.x - s * ax.z;
	tMat[1][1] = c + (1 - c) * ax.y * ax.y;
	tMat[1][2] = (1 - c) * ax.y * ax.z + s * ax.x;
	tMat[1][3] = 0;

	tMat[2][0] = (1 - c) * ax.z * ax.x + s * ax.y;
	tMat[2][1] = (1 - c) * ax.z * ax.y - s * ax.x;
	tMat[2][2] = c + (1 - c) * ax.z * ax.z;
	tMat[2][3] = 0;

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
