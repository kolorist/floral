#pragma once

#include <cstring>

#include <stdaliases.h>

#include "vec.h"

/*
 * IMPORTANT: Matrix and Vector math convention
 * 	in Memory: m0 m1 m2 m3 m4 ...
 * 	Math Convention (for both GPU and CPU)
 * 		Vector(in Parent) = Matrix(Child to Parent) * Vector(in Child);
 *
 * 	GPU: column-major (because we are storing sequential by columns)
 * 		matrix *math* layout from memory:
 * 			m0	m4	m8	m12
 * 			m1	m5	m9	m13
 * 			m2	m6	m10	m14
 * 			m3	m7	m11	m15
 * 		vector *math* layout:
 * 			m0
 * 			m1
 * 			m2
 * 			m3
 *
 * 	CPU: column-major (to not break the column-major notation of OpenGL)
 */

namespace floral {

template <class t_type>
struct mat3x3 {
	typedef t_type								column_t[3];

	mat3x3()
	{
		memset(cols, 0, sizeof(cols));
	}

	mat3x3(const vec3<t_type>& r1, const vec3<t_type>& r2, const vec3<t_type>& r3)
	{
		cols[0][0] = r1.x; cols[0][1] = r1.y; cols[0][2] = r1.z;
		cols[1][0] = r2.x; cols[1][1] = r2.y; cols[1][2] = r2.z;
		cols[2][0] = r3.x; cols[2][1] = r3.y; cols[2][2] = r3.z;
	}

	// noone should do this, this is ridiculous -.-!
	mat3x3(column_t cols[])
	{
		cols[0][0] = cols[0][0]; cols[0][1] = cols[0][1]; cols[0][2] = cols[0][2];
		cols[1][0] = cols[1][0]; cols[1][1] = cols[1][1]; cols[1][2] = cols[1][2];
		cols[2][0] = cols[2][0]; cols[2][1] = cols[2][1]; cols[2][2] = cols[2][2];
	}

	explicit mat3x3(const t_type val)
	{
		memset(cols, 0, sizeof(cols));
		cols[0][0] = val;
		cols[1][1] = val;
		cols[2][2] = val;
	}

	mat3x3(const mat3x3& other)
	{
		cols[0][0] = other[0][0]; cols[0][1] = other[0][1]; cols[0][2] = other[0][2];
		cols[1][0] = other[1][0]; cols[1][1] = other[1][1]; cols[1][2] = other[1][2];
		cols[2][0] = other[2][0]; cols[2][1] = other[2][1]; cols[2][2] = other[2][2];
	}

	////////////////////////////////////////
	mat3x3 operator*(const mat3x3& other) const {
		t_type r00 = cols[0][0] * other[0][0] + cols[0][1] * other[1][0] + cols[0][2] * other[2][0];
		t_type r01 = cols[0][0] * other[0][1] + cols[0][1] * other[1][1] + cols[0][2] * other[2][1];
		t_type r02 = cols[0][0] * other[0][2] + cols[0][1] * other[1][2] + cols[0][2] * other[2][2];

		t_type r10 = cols[1][0] * other[0][0] + cols[1][1] * other[1][0] + cols[1][2] * other[2][0];
		t_type r11 = cols[1][0] * other[0][1] + cols[1][1] * other[1][1] + cols[1][2] * other[2][1];
		t_type r12 = cols[1][0] * other[0][2] + cols[1][1] * other[1][2] + cols[1][2] * other[2][2];

		t_type r20 = cols[2][0] * other[0][0] + cols[2][1] * other[1][0] + cols[2][2] * other[2][0];
		t_type r21 = cols[2][0] * other[0][1] + cols[2][1] * other[1][1] + cols[2][2] * other[2][1];
		t_type r22 = cols[2][0] * other[0][2] + cols[2][1] * other[1][2] + cols[2][2] * other[2][2];

		mat3x3 tMat(
				{r00, r01, r02},
				{r10, r11, r12},
				{r20, r21, r22});
		return tMat;
	}

	mat3x3 operator*(const t_type scalar) const {
		return mat3x3(
				{cols[0][0] * scalar, cols[0][1] * scalar, cols[0][2] * scalar},
				{cols[1][0] * scalar, cols[1][1] * scalar, cols[1][2] * scalar},
				{cols[2][0] * scalar, cols[2][1] * scalar, cols[2][2] * scalar});
	}

	mat3x3 operator*=(const t_type scalar) {
		cols[0][0] *= scalar; cols[0][1] *= scalar; cols[0][2] *= scalar;
		cols[1][0] *= scalar; cols[1][1] *= scalar; cols[1][2] *= scalar;
		cols[2][0] *= scalar; cols[2][1] *= scalar; cols[2][2] *= scalar;
		return (*this);
	}

	mat3x3 operator/(const t_type scalar) {
		return mat3x3(
				{cols[0][0] / scalar, cols[0][1] / scalar, cols[0][2] / scalar},
				{cols[1][0] / scalar, cols[1][1] / scalar, cols[1][2] / scalar},
				{cols[2][0] / scalar, cols[2][1] / scalar, cols[2][2] / scalar});
	}

	mat3x3 operator/=(const t_type scalar) {
		cols[0][0] /= scalar; cols[0][1] /= scalar; cols[0][2] /= scalar;
		cols[1][0] /= scalar; cols[1][1] /= scalar; cols[1][2] /= scalar;
		cols[2][0] /= scalar; cols[2][1] /= scalar; cols[2][2] /= scalar;
		return (*this);
	}

	const bool operator==(const mat3x3& other) {
		return (cols[0][0] == other[0][0] && cols[0][1] == other[0][1] && cols[0][2] == other[0][2] &&
				cols[1][0] == other[1][0] && cols[1][1] == other[1][1] && cols[1][2] == other[1][2] &&
				cols[2][0] == other[2][0] && cols[2][1] == other[2][1] && cols[2][2] == other[2][2]);
	}

	column_t& operator[](const u32 colIdx) {
		return cols[colIdx];
	}

	const column_t& operator[](const u32 colIdx) const {
		return cols[colIdx];
	}

	////////////////////////////////////////
	const t_type get_determinant() const 
	{
		t_type d00 = cols[1][1] * cols[2][2] - cols[2][1] * cols[1][2];
		t_type d01 = cols[1][0] * cols[2][2] - cols[2][0] * cols[1][2];
		t_type d02 = cols[1][0] * cols[2][1] - cols[2][0] * cols[1][1];

		return (cols[0][0] * d00 - cols[0][1] * d01 + cols[0][2] * d02);
	}

	mat3x3 get_inverse() const 
	{
		t_type d00 = cols[1][1] * cols[2][2] - cols[2][1] * cols[1][2];
		t_type d01 = cols[1][0] * cols[2][2] - cols[2][0] * cols[1][2];
		t_type d02 = cols[1][0] * cols[2][1] - cols[2][0] * cols[1][1];

		t_type d10 = cols[0][1] * cols[2][2] - cols[2][1] * cols[0][2];
		t_type d11 = cols[0][0] * cols[2][2] - cols[2][0] * cols[0][2];
		t_type d12 = cols[0][0] * cols[2][1] - cols[2][0] * cols[0][1];

		t_type d20 = cols[0][1] * cols[1][2] - cols[1][1] * cols[0][2];
		t_type d21 = cols[0][0] * cols[1][2] - cols[1][0] * cols[0][2];
		t_type d22 = cols[0][0] * cols[1][1] - cols[1][0] * cols[0][1];

		t_type d = cols[0][0] * d00 - cols[0][1] * d01 + cols[0][2] * d02;
		// apply
		// + - +
		// - + -
		// + - +
		// and then tranpose
		mat3x3 tMat(
				{d00, -d10, d20},
				{-d01, d11, -d21},
				{d02, -d12, d22});
		tMat /= d;
		return tMat;
	}

	mat3x3 get_transpose() const
	{
		mat3x3 tMat(
				{cols[0][0], cols[1][0], cols[2][0]},
				{cols[0][1], cols[1][1], cols[2][1]},
				{cols[0][2], cols[1][2], cols[2][2]});
		return tMat;
	}

	//--------------------------------------
	column_t									cols[3];
};

template <class t_type>
struct mat4x4 {
	typedef t_type								column_t[4];

	mat4x4()
	{
		memset(cols, 0, sizeof(cols));
	}

	mat4x4(const vec4<t_type>& r1, const vec4<t_type>& r2, const vec4<t_type>& r3, const vec4<t_type>& r4)
	{
		cols[0][0] = r1.x; cols[0][1] = r1.y; cols[0][2] = r1.z; cols[0][3] = r1.w;
		cols[1][0] = r2.x; cols[1][1] = r2.y; cols[1][2] = r2.z; cols[1][3] = r2.w;
		cols[2][0] = r3.x; cols[2][1] = r3.y; cols[2][2] = r3.z; cols[2][3] = r3.w;
		cols[3][0] = r4.x; cols[3][1] = r4.y; cols[3][2] = r4.z; cols[3][3] = r4.w;
	}

	explicit mat4x4(const t_type val)
	{
		memset(cols, 0, sizeof(cols));
		cols[0][0] = val;
		cols[1][1] = val;
		cols[2][2] = val;
		cols[3][3] = val;
	}

	mat4x4(const mat4x4& other)
	{
		cols[0][0] = other[0][0]; cols[0][1] = other[0][1]; cols[0][2] = other[0][2]; cols[0][3] = other[0][3];
		cols[1][0] = other[1][0]; cols[1][1] = other[1][1]; cols[1][2] = other[1][2]; cols[1][3] = other[1][3];
		cols[2][0] = other[2][0]; cols[2][1] = other[2][1]; cols[2][2] = other[2][2]; cols[2][3] = other[2][3];
		cols[3][0] = other[3][0]; cols[3][1] = other[3][1]; cols[3][2] = other[3][2]; cols[3][3] = other[3][3];
	}
	
	////////////////////////////////////////
	const t_type get_determinant() const
	{
		t_type d0 = get_determinant3x3(
				cols[1][1], cols[1][2], cols[1][3],
				cols[2][1], cols[2][2], cols[2][3],
				cols[3][1], cols[3][2], cols[3][3]);
		t_type d1 = get_determinant3x3(
				cols[1][0], cols[1][2], cols[1][3],
				cols[2][0], cols[2][2], cols[2][3],
				cols[3][0], cols[3][2], cols[3][3]);
		t_type d2 = get_determinant3x3(
				cols[1][0], cols[1][1], cols[1][3],
				cols[2][0], cols[2][1], cols[2][3],
				cols[3][0], cols[3][1], cols[3][3]);
		t_type d3 = get_determinant3x3(
				cols[1][0], cols[1][1], cols[1][2],
				cols[2][0], cols[2][1], cols[2][2],
				cols[3][0], cols[3][1], cols[3][2]);
		return (cols[0][0] * d0 - cols[0][1] * d1 + cols[0][2] * d2 - cols[0][3] * d3);
	}

	mat4x4 get_inverse() const
	{
		t_type d00 = get_determinant3x3(
				cols[1][1], cols[1][2], cols[1][3], cols[2][1], cols[2][2], cols[2][3],	cols[3][1], cols[3][2], cols[3][3]);
		t_type d01 = get_determinant3x3(
				cols[1][0], cols[1][2], cols[1][3],	cols[2][0], cols[2][2], cols[2][3],	cols[3][0], cols[3][2], cols[3][3]);
		t_type d02 = get_determinant3x3(
				cols[1][0], cols[1][1], cols[1][3],	cols[2][0], cols[2][1], cols[2][3],	cols[3][0], cols[3][1], cols[3][3]);
		t_type d03 = get_determinant3x3(
				cols[1][0], cols[1][1], cols[1][2],	cols[2][0], cols[2][1], cols[2][2],	cols[3][0], cols[3][1], cols[3][2]);

		t_type d10 = get_determinant3x3(
				cols[0][1], cols[0][2], cols[0][3], cols[2][1], cols[2][2], cols[2][3], cols[3][1], cols[3][2], cols[3][3]);
		t_type d11 = get_determinant3x3(
				cols[0][0], cols[0][2], cols[0][3], cols[2][0], cols[2][2], cols[2][3], cols[3][0], cols[3][2], cols[3][3]);
		t_type d12 = get_determinant3x3(
				cols[0][0], cols[0][1], cols[0][3],	cols[2][0], cols[2][1], cols[2][3],	cols[3][0], cols[3][1], cols[3][3]);
		t_type d13 = get_determinant3x3(
				cols[0][0], cols[0][1], cols[0][2],	cols[2][0], cols[2][1], cols[2][2],	cols[3][0], cols[3][1], cols[3][2]);

		t_type d20 = get_determinant3x3(
				cols[0][1], cols[0][2], cols[0][3], cols[1][1], cols[1][2], cols[1][3], cols[3][1], cols[3][2], cols[3][3]);
		t_type d21 = get_determinant3x3(
				cols[0][0], cols[0][2], cols[0][3], cols[1][0], cols[1][2], cols[1][3], cols[3][0], cols[3][2], cols[3][3]);
		t_type d22 = get_determinant3x3(
				cols[0][0], cols[0][1], cols[0][3],	cols[1][0], cols[1][1], cols[1][3],	cols[3][0], cols[3][1], cols[3][3]);
		t_type d23 = get_determinant3x3(
				cols[0][0], cols[0][1], cols[0][2],	cols[1][0], cols[1][1], cols[1][2],	cols[3][0], cols[3][1], cols[3][2]);

		t_type d30 = get_determinant3x3(
				cols[0][1], cols[0][2], cols[0][3], cols[1][1], cols[1][2], cols[1][3], cols[2][1], cols[2][2], cols[2][3]);
		t_type d31 = get_determinant3x3(
				cols[0][0], cols[0][2], cols[0][3], cols[1][0], cols[1][2], cols[1][3], cols[2][0], cols[2][2], cols[2][3]);
		t_type d32 = get_determinant3x3(
				cols[0][0], cols[0][1], cols[0][3],	cols[1][0], cols[1][1], cols[1][3],	cols[2][0], cols[2][1], cols[2][3]);
		t_type d33 = get_determinant3x3(
				cols[0][0], cols[0][1], cols[0][2],	cols[1][0], cols[1][1], cols[1][2],	cols[2][0], cols[2][1], cols[2][2]);

		t_type d = cols[0][0] * d00 - cols[0][1] * d01 + cols[0][2] * d02 - cols[0][3] * d03;
		// apply
		// + - + -
		// - + - +
		// + - + -
		// - + - +
		// and then transpose
		mat4x4 tMat(
				{d00, -d10, d20, -d30},
				{-d01, d11, -d21, d31},
				{d02, -d12, d22, -d32},
				{-d03, d13, -d23, d33});
		tMat /= d;
		return tMat;
	}

	mat4x4 get_transpose() const
	{
		mat4x4 tMat(
				{cols[0][0], cols[1][0], cols[2][0], cols[3][0]},
				{cols[0][1], cols[1][1], cols[2][1], cols[3][1]},
				{cols[0][2], cols[1][2], cols[2][2], cols[3][2]},
				{cols[0][3], cols[1][3], cols[2][3], cols[3][3]});
		return tMat;
	}

	////////////////////////////////////////
	mat4x4 operator*(const t_type scalar) const {
		return mat4x4(
				{cols[0][0] * scalar, cols[0][1] * scalar, cols[0][2] * scalar, cols[0][3] * scalar},
				{cols[1][0] * scalar, cols[1][1] * scalar, cols[1][2] * scalar, cols[1][3] * scalar},
				{cols[2][0] * scalar, cols[2][1] * scalar, cols[2][2] * scalar, cols[2][3] * scalar},
				{cols[3][0] * scalar, cols[3][1] * scalar, cols[3][2] * scalar, cols[3][3] * scalar});
	}

	mat4x4 operator*(const mat4x4& other) const {
		t_type c00 = cols[0][0] * other[0][0] + cols[1][0] * other[0][1] + cols[2][0] * other[0][2] + cols[3][0] * other[0][3];
		t_type c01 = cols[0][1] * other[0][0] + cols[1][1] * other[0][1] + cols[2][1] * other[0][2] + cols[3][1] * other[0][3];
		t_type c02 = cols[0][2] * other[0][0] + cols[1][2] * other[0][1] + cols[2][2] * other[0][2] + cols[3][2] * other[0][3];
		t_type c03 = cols[0][3] * other[0][0] + cols[1][3] * other[0][1] + cols[2][3] * other[0][2] + cols[3][3] * other[0][3];

		t_type c10 = cols[0][0] * other[1][0] + cols[1][0] * other[1][1] + cols[2][0] * other[1][2] + cols[3][0] * other[1][3];
		t_type c11 = cols[0][1] * other[1][0] + cols[1][1] * other[1][1] + cols[2][1] * other[1][2] + cols[3][1] * other[1][3];
		t_type c12 = cols[0][2] * other[1][0] + cols[1][2] * other[1][1] + cols[2][2] * other[1][2] + cols[3][2] * other[1][3];
		t_type c13 = cols[0][3] * other[1][0] + cols[1][3] * other[1][1] + cols[2][3] * other[1][2] + cols[3][3] * other[1][3];

		t_type c20 = cols[0][0] * other[2][0] + cols[1][0] * other[2][1] + cols[2][0] * other[2][2] + cols[3][0] * other[2][3];
		t_type c21 = cols[0][1] * other[2][0] + cols[1][1] * other[2][1] + cols[2][1] * other[2][2] + cols[3][1] * other[2][3];
		t_type c22 = cols[0][2] * other[2][0] + cols[1][2] * other[2][1] + cols[2][2] * other[2][2] + cols[3][2] * other[2][3];
		t_type c23 = cols[0][3] * other[2][0] + cols[1][3] * other[2][1] + cols[2][3] * other[2][2] + cols[3][3] * other[2][3];

		t_type c30 = cols[0][0] * other[3][0] + cols[1][0] * other[3][1] + cols[2][0] * other[3][2] + cols[3][0] * other[3][3];
		t_type c31 = cols[0][1] * other[3][0] + cols[1][1] * other[3][1] + cols[2][1] * other[3][2] + cols[3][1] * other[3][3];
		t_type c32 = cols[0][2] * other[3][0] + cols[1][2] * other[3][1] + cols[2][2] * other[3][2] + cols[3][2] * other[3][3];
		t_type c33 = cols[0][3] * other[3][0] + cols[1][3] * other[3][1] + cols[2][3] * other[3][2] + cols[3][3] * other[3][3];

		mat4x4 tMat(
				{c00, c01, c02, c03},
				{c10, c11, c12, c13},
				{c20, c21, c22, c23},
				{c30, c31, c32, c33});
		return tMat;
	}

	mat4x4 operator*=(const t_type scalar) const {
		cols[0][0] *= scalar; cols[0][1] *= scalar; cols[0][2] *= scalar; cols[0][3] *= scalar;
		cols[1][0] *= scalar; cols[1][1] *= scalar; cols[1][2] *= scalar; cols[1][3] *= scalar;
		cols[2][0] *= scalar; cols[2][1] *= scalar; cols[2][2] *= scalar; cols[2][3] *= scalar;
		cols[3][0] *= scalar; cols[3][1] *= scalar; cols[3][2] *= scalar; cols[3][3] *= scalar;
		return (*this);
	}

	mat4x4 operator/(const t_type scalar) {
		return mat4x4(
				{cols[0][0] / scalar, cols[0][1] / scalar, cols[0][2] / scalar, cols[0][3] / scalar},
				{cols[1][0] / scalar, cols[1][1] / scalar, cols[1][2] / scalar, cols[1][3] / scalar},
				{cols[2][0] / scalar, cols[2][1] / scalar, cols[2][2] / scalar, cols[2][3] / scalar},
				{cols[3][0] / scalar, cols[3][1] / scalar, cols[3][2] / scalar, cols[3][3] / scalar});
	}

	mat4x4 operator/=(const t_type scalar) {
		cols[0][0] /= scalar; cols[0][1] /= scalar; cols[0][2] /= scalar; cols[0][3] /= scalar;
		cols[1][0] /= scalar; cols[1][1] /= scalar; cols[1][2] /= scalar; cols[1][3] /= scalar;
		cols[2][0] /= scalar; cols[2][1] /= scalar; cols[2][2] /= scalar; cols[2][3] /= scalar;
		cols[3][0] /= scalar; cols[3][1] /= scalar; cols[3][2] /= scalar; cols[3][3] /= scalar;
		return (*this);
	}

	const bool operator==(const mat4x4& other) {
		return (cols[0][0] == other[0][0] && cols[0][1] == other[0][1] && cols[0][2] == other[0][2] && cols[0][3] == other[0][3] &&
				cols[1][0] == other[1][0] && cols[1][1] == other[1][1] && cols[1][2] == other[1][2] && cols[1][3] == other[1][3] &&
				cols[2][0] == other[2][0] && cols[2][1] == other[2][1] && cols[2][2] == other[2][2] && cols[2][3] == other[2][3] &&
				cols[3][0] == other[3][0] && cols[3][1] == other[3][1] && cols[3][2] == other[3][2] && cols[3][3] == other[3][3]
				);
	}

	column_t& operator[](const u32 colIdx) {
		return cols[colIdx];
	}

	const column_t& operator[](const u32 colIdx) const {
		return cols[colIdx];
	}

	//--------------------------------------
	column_t									cols[4];
	//--------------------------------------
private:
	inline const t_type get_determinant3x3(
			t_type m00, t_type m01, t_type m02,
			t_type m10, t_type m11, t_type m12,
			t_type m20, t_type m21, t_type m22) const
	{
		t_type d0 = m11 * m22 - m21 * m12;
		t_type d1 = m10 * m22 - m20 * m12;
		t_type d2 = m10 * m21 - m20 * m11;
		return (m00 * d0 - m01 * d1 + m02 * d2);
	}

};

////////////////////////////////////////////
using mat3x3f = mat3x3<f32>;
using mat3x3i = mat3x3<s32>;
using mat4x4f = mat4x4<f32>;
using mat4x4i = mat4x4<s32>;

////////////////////////////////////////////
// notation: column-major matrix X column vector
template <class t_vec, class t_mat>
vec3<t_vec> operator*(const mat3x3<t_mat>& m, const vec3<t_vec>& v) {
	return vec3<t_vec>(
			m[0][0] * v.x, m[1][0] * v.y, m[2][0] * v.z,
			m[0][1] * v.x, m[1][1] * v.y, m[2][1] * v.z,
			m[0][2] * v.x, m[1][2] * v.y, m[2][2] * v.z
			);
}

template <class t_vec, class t_mat>
vec4<t_vec> operator*(const mat4x4<t_mat>& m, const vec4<t_vec>& v) {
	return vec4<t_vec>(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
			m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w
			);
}

}
