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
mat4x4f construct_translation3d(const f32 i_deltaX, const f32 i_deltaY, const f32 i_deltaZ)
{
	mat4x4f tMat = mat4x4f(1.0f);
	tMat[3][0] = i_deltaX;
	tMat[3][1] = i_deltaY;
	tMat[3][2] = i_deltaZ;
	return tMat;
}

mat4x4f construct_translation3d(const vec3f& i_delta)
{
	mat4x4f tMat = mat4x4f(1.0f);
	tMat[3][0] = i_delta.x;
	tMat[3][1] = i_delta.y;
	tMat[3][2] = i_delta.z;
	return tMat;
}

mat4x4f construct_scaling3d(const f32 i_scaleX, const f32 i_scaleY, const f32 i_scaleZ)
{
	mat4x4f tMat;
	tMat[0][0] = i_scaleX;
	tMat[1][1] = i_scaleY;
	tMat[2][2] = i_scaleZ;
	tMat[3][3] = 1.0f;
	return tMat;
}

mat4x4f construct_scaling3d(const vec3f& i_scale)
{
	mat4x4f tMat;
	tMat[0][0] = i_scale.x;
	tMat[1][1] = i_scale.y;
	tMat[2][2] = i_scale.z;
	tMat[3][3] = 1.0f;
	return tMat;
}

mat4x4f construct_Xrotation3d(f32 i_rX)
{
	mat4x4f tMat;
	tMat[0][0] = 1.0f;
	tMat[1][1] = cosf(i_rX);
	tMat[1][2] = -sinf(i_rX);
	tMat[2][1] = sinf(i_rX);
	tMat[2][2] = cosf(i_rX);
	tMat[3][3] = 1.0f;
	return tMat;
}

mat4x4f construct_Yrotation3d(f32 i_rY)
{
	mat4x4f tMat;
	tMat[0][0] = cosf(i_rY);
	tMat[0][2] = sinf(i_rY);
	tMat[1][1] = 1.0f;
	tMat[2][0] = -sinf(i_rY);
	tMat[2][2] = cosf(i_rY);
	tMat[3][3] = 1.0f;
	return tMat;
}

mat4x4f construct_Zrotation3d(f32 i_rZ)
{
	mat4x4f tMat;
	tMat[0][0] = cosf(i_rZ);
	tMat[0][1] = -sinf(i_rZ);
	tMat[1][0] = sinf(i_rZ);
	tMat[1][1] = cosf(i_rZ);
	tMat[2][2] = 1.0f;
	tMat[3][3] = 1.0f;
	return tMat;
}

mat4x4f construct_axis_rotation3d(const vec3f& i_axis, const f32 i_angle)
{
	mat4x4f tMat;
	f32 c = cosf(i_angle);
	f32 s = sinf(i_angle);

	vec3f ax = normalize(i_axis);

	tMat[0][0] = c + (1 - c) * ax.x * ax.x;
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

quaternionf construct_quaternion_euler(const vec3f& i_r)
{
	return construct_quaternion_euler(i_r.x, i_r.y, i_r.z);
}

quaternionf construct_quaternion_euler(const f32 i_rx, const f32 i_ry, const f32 i_rz)
{
	// TODO: optimize this!!!
	quaternionf qX, qY, qZ;
	f32 halfThetaX = floral::to_radians(i_rx) / 2.0f;
	f32 halfThetaY = floral::to_radians(i_ry) / 2.0f;
	f32 halfThetaZ = floral::to_radians(i_rz) / 2.0f;
	qX.v = floral::vec3f(-sinf(halfThetaX), 0.0f, 0.0f);
	qX.w = cosf(halfThetaX);
	qY.v = floral::vec3f(0.0f, -sinf(halfThetaY), 0.0f);
	qY.w = cosf(halfThetaY);
	qZ.v = floral::vec3f(0.0f, 0.0f, -sinf(halfThetaZ));
	qZ.w = cosf(halfThetaZ);
	return qX * qY * qZ;
}

quaternionf construct_quaternion_axis(const vec3f& i_axis, const f32 i_r)
{
	quaternionf q;
	//vec3f n = normalize(i_axis);
	f32 halfTheta = floral::to_radians(i_r) / 2.0f;
	q.v = -i_axis * sinf(halfTheta);
	q.w = cosf(halfTheta);
	return q;
}

mat4x4f construct_invert(const mat4x4f& i_m)
{
	mat4x4f tMat;
	return tMat;
}

mat3x3f construct_invert(const mat3x3f& i_m)
{
	mat3x3f tMat;
	return tMat;
}

mat4x4f construct_transpose(const mat4x4f& i_m)
{
	mat4x4f tMat;
	tMat[0][0] = i_m[0][0]; tMat[0][1] = i_m[1][0]; tMat[0][2] = i_m[2][0]; tMat[0][3] = i_m[3][0];
	tMat[1][0] = i_m[0][1]; tMat[1][1] = i_m[1][1]; tMat[1][2] = i_m[2][1]; tMat[1][3] = i_m[3][1];
	tMat[2][0] = i_m[0][2]; tMat[2][1] = i_m[1][2]; tMat[2][2] = i_m[2][2]; tMat[2][3] = i_m[3][2];
	tMat[3][0] = i_m[0][3]; tMat[3][1] = i_m[1][3]; tMat[3][2] = i_m[2][3]; tMat[3][3] = i_m[3][3];
	return tMat;
}

mat3x3f construct_transpose(const mat3x3f& i_m)
{
	mat3x3f tMat;
	tMat[0][0] = i_m[0][0]; tMat[0][1] = i_m[1][0]; tMat[0][2] = i_m[2][0];
	tMat[1][0] = i_m[0][1]; tMat[1][1] = i_m[1][1]; tMat[1][2] = i_m[2][1];
	tMat[2][0] = i_m[0][2]; tMat[2][1] = i_m[1][2]; tMat[2][2] = i_m[2][2];
	return tMat;
}
}
