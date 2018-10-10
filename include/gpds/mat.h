#ifndef __FLORAL_MAT_H__
#define __FLORAL_MAT_H__

#include <cstring>

#include <stdaliases.h>

#include "vec.h"

/*
 * IMPORTANT: Matrix and Vector math convention
 * 	in Memory: m0 m1 m2 m3 m4 ...
 * 	Math Convention (for both GLSL and CPU)
 * 		Vector(in Parent) = Matrix(Child to Parent) * Vector(in Child);
 *
 * 	GLSL: column-major (because we are storing sequential by columns)
 * 		matrix math layout from memory:
 * 			m0	m4	m8	m12
 * 			m1	m5	m9	m13
 * 			m2	m6	m10	m14
 * 			m3	m7	m11	m15
 * 		vector layout:
 * 			m0
 * 			m1
 * 			m2
 * 			m3
 *
 * 	CPU: column-major (to not break the column-major notation of OpenGL)
 */

namespace floral {

template <class DType>
struct mat3x3 {
	typedef DType							ColType[3];

	mat3x3()
	{
		memset(Cols, 0, sizeof(Cols));
	}

	mat3x3(const vec3<DType>& r1, const vec3<DType>& r2, const vec3<DType>& r3)
	{
		Cols[0][0] = r1.x; Cols[0][1] = r1.y; Cols[0][2] = r1.z;
		Cols[1][0] = r2.x; Cols[1][1] = r2.y; Cols[1][2] = r2.z;
		Cols[2][0] = r3.x; Cols[2][1] = r3.y; Cols[2][2] = r3.z;
	}

	// noone should do this, this is ridiculous -.-!
	mat3x3(ColType Cols[])
	{
		Cols[0][0] = Cols[0][0]; Cols[0][1] = Cols[0][1]; Cols[0][2] = Cols[0][2];
		Cols[1][0] = Cols[1][0]; Cols[1][1] = Cols[1][1]; Cols[1][2] = Cols[1][2];
		Cols[2][0] = Cols[2][0]; Cols[2][1] = Cols[2][1]; Cols[2][2] = Cols[2][2];
	}

	explicit mat3x3(const DType val)
	{
		memset(Cols, 0, sizeof(Cols));
		Cols[0][0] = val;
		Cols[1][1] = val;
		Cols[2][2] = val;
	}

	mat3x3(const mat3x3& other)
	{
		Cols[0][0] = other[0][0]; Cols[0][1] = other[0][1]; Cols[0][2] = other[0][2];
		Cols[1][0] = other[1][0]; Cols[1][1] = other[1][1]; Cols[1][2] = other[1][2];
		Cols[2][0] = other[2][0]; Cols[2][1] = other[2][1]; Cols[2][2] = other[2][2];
	}

	////////////////////////////////////////
	mat3x3 operator*(const mat3x3& other) const {
		DType r00 = Cols[0][0] * other[0][0] + Cols[0][1] * other[1][0] + Cols[0][2] * other[2][0];
		DType r01 = Cols[0][0] * other[0][1] + Cols[0][1] * other[1][1] + Cols[0][2] * other[2][1];
		DType r02 = Cols[0][0] * other[0][2] + Cols[0][1] * other[1][2] + Cols[0][2] * other[2][2];

		DType r10 = Cols[1][0] * other[0][0] + Cols[1][1] * other[1][0] + Cols[1][2] * other[2][0];
		DType r11 = Cols[1][0] * other[0][1] + Cols[1][1] * other[1][1] + Cols[1][2] * other[2][1];
		DType r12 = Cols[1][0] * other[0][2] + Cols[1][1] * other[1][2] + Cols[1][2] * other[2][2];

		DType r20 = Cols[2][0] * other[0][0] + Cols[2][1] * other[1][0] + Cols[2][2] * other[2][0];
		DType r21 = Cols[2][0] * other[0][1] + Cols[2][1] * other[1][1] + Cols[2][2] * other[2][1];
		DType r22 = Cols[2][0] * other[0][2] + Cols[2][1] * other[1][2] + Cols[2][2] * other[2][2];

		mat3x3 tMat(
				{r00, r01, r02},
				{r10, r11, r12},
				{r20, r21, r22});
		return tMat;
	}

	mat3x3 operator*(const DType scalar) const {
		return mat3x3(
				{Cols[0][0] * scalar, Cols[0][1] * scalar, Cols[0][2] * scalar},
				{Cols[1][0] * scalar, Cols[1][1] * scalar, Cols[1][2] * scalar},
				{Cols[2][0] * scalar, Cols[2][1] * scalar, Cols[2][2] * scalar});
	}

	mat3x3 operator*=(const DType scalar) {
		Cols[0][0] *= scalar; Cols[0][1] *= scalar; Cols[0][2] *= scalar;
		Cols[1][0] *= scalar; Cols[1][1] *= scalar; Cols[1][2] *= scalar;
		Cols[2][0] *= scalar; Cols[2][1] *= scalar; Cols[2][2] *= scalar;
		return (*this);
	}

	mat3x3 operator/(const DType scalar) {
		return mat3x3(
				{Cols[0][0] / scalar, Cols[0][1] / scalar, Cols[0][2] / scalar},
				{Cols[1][0] / scalar, Cols[1][1] / scalar, Cols[1][2] / scalar},
				{Cols[2][0] / scalar, Cols[2][1] / scalar, Cols[2][2] / scalar});
	}

	mat3x3 operator/=(const DType scalar) {
		Cols[0][0] /= scalar; Cols[0][1] /= scalar; Cols[0][2] /= scalar;
		Cols[1][0] /= scalar; Cols[1][1] /= scalar; Cols[1][2] /= scalar;
		Cols[2][0] /= scalar; Cols[2][1] /= scalar; Cols[2][2] /= scalar;
		return (*this);
	}

	const bool operator==(const mat3x3& other) {
		return (Cols[0][0] == other[0][0] && Cols[0][1] == other[0][1] && Cols[0][2] == other[0][2] &&
				Cols[1][0] == other[1][0] && Cols[1][1] == other[1][1] && Cols[1][2] == other[1][2] &&
				Cols[2][0] == other[2][0] && Cols[2][1] == other[2][1] && Cols[2][2] == other[2][2]);
	}

	ColType& operator[](const u32 colIdx) {
		return Cols[colIdx];
	}

	const ColType& operator[](const u32 colIdx) const {
		return Cols[colIdx];
	}

	////////////////////////////////////////
	const DType get_determinant() const 
	{
		DType d00 = Cols[1][1] * Cols[2][2] - Cols[2][1] * Cols[1][2];
		DType d01 = Cols[1][0] * Cols[2][2] - Cols[2][0] * Cols[1][2];
		DType d02 = Cols[1][0] * Cols[2][1] - Cols[2][0] * Cols[1][1];

		return (Cols[0][0] * d00 - Cols[0][1] * d01 + Cols[0][2] * d02);
	}

	mat3x3 get_inverse() const 
	{
		DType d00 = Cols[1][1] * Cols[2][2] - Cols[2][1] * Cols[1][2];
		DType d01 = Cols[1][0] * Cols[2][2] - Cols[2][0] * Cols[1][2];
		DType d02 = Cols[1][0] * Cols[2][1] - Cols[2][0] * Cols[1][1];

		DType d10 = Cols[0][1] * Cols[2][2] - Cols[2][1] * Cols[0][2];
		DType d11 = Cols[0][0] * Cols[2][2] - Cols[2][0] * Cols[0][2];
		DType d12 = Cols[0][0] * Cols[2][1] - Cols[2][0] * Cols[0][1];

		DType d20 = Cols[0][1] * Cols[1][2] - Cols[1][1] * Cols[0][2];
		DType d21 = Cols[0][0] * Cols[1][2] - Cols[1][0] * Cols[0][2];
		DType d22 = Cols[0][0] * Cols[1][1] - Cols[1][0] * Cols[0][1];

		DType d = Cols[0][0] * d00 - Cols[0][1] * d01 + Cols[0][2] * d02;
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
				{Cols[0][0], Cols[1][0], Cols[2][0]},
				{Cols[0][1], Cols[1][1], Cols[2][1]},
				{Cols[0][2], Cols[1][2], Cols[2][2]});
		return tMat;
	}

	//--------------------------------------
	ColType									Cols[3];
};

template <class DType>
struct mat4x4 {
	typedef DType							ColType[4];

	mat4x4()
	{
		memset(Cols, 0, sizeof(Cols));
	}

	mat4x4(const vec4<DType>& r1, const vec4<DType>& r2, const vec4<DType>& r3, const vec4<DType>& r4)
	{
		Cols[0][0] = r1.x; Cols[0][1] = r1.y; Cols[0][2] = r1.z; Cols[0][3] = r1.w;
		Cols[1][0] = r2.x; Cols[1][1] = r2.y; Cols[1][2] = r2.z; Cols[1][3] = r2.w;
		Cols[2][0] = r3.x; Cols[2][1] = r3.y; Cols[2][2] = r3.z; Cols[2][3] = r3.w;
		Cols[3][0] = r4.x; Cols[3][1] = r4.y; Cols[3][2] = r4.z; Cols[3][3] = r4.w;
	}

	explicit mat4x4(const DType val)
	{
		memset(Cols, 0, sizeof(Cols));
		Cols[0][0] = val;
		Cols[1][1] = val;
		Cols[2][2] = val;
		Cols[3][3] = val;
	}

	mat4x4(const mat4x4& other)
	{
		Cols[0][0] = other[0][0]; Cols[0][1] = other[0][1]; Cols[0][2] = other[0][2]; Cols[0][3] = other[0][3];
		Cols[1][0] = other[1][0]; Cols[1][1] = other[1][1]; Cols[1][2] = other[1][2]; Cols[1][3] = other[1][3];
		Cols[2][0] = other[2][0]; Cols[2][1] = other[2][1]; Cols[2][2] = other[2][2]; Cols[2][3] = other[2][3];
		Cols[3][0] = other[3][0]; Cols[3][1] = other[3][1]; Cols[3][2] = other[3][2]; Cols[3][3] = other[3][3];
	}
	
	////////////////////////////////////////
	const DType get_determinant() const
	{
		DType d0 = get_determinant3x3(
				Cols[1][1], Cols[1][2], Cols[1][3],
				Cols[2][1], Cols[2][2], Cols[2][3],
				Cols[3][1], Cols[3][2], Cols[3][3]);
		DType d1 = get_determinant3x3(
				Cols[1][0], Cols[1][2], Cols[1][3],
				Cols[2][0], Cols[2][2], Cols[2][3],
				Cols[3][0], Cols[3][2], Cols[3][3]);
		DType d2 = get_determinant3x3(
				Cols[1][0], Cols[1][1], Cols[1][3],
				Cols[2][0], Cols[2][1], Cols[2][3],
				Cols[3][0], Cols[3][1], Cols[3][3]);
		DType d3 = get_determinant3x3(
				Cols[1][0], Cols[1][1], Cols[1][2],
				Cols[2][0], Cols[2][1], Cols[2][2],
				Cols[3][0], Cols[3][1], Cols[3][2]);
		return (Cols[0][0] * d0 - Cols[0][1] * d1 + Cols[0][2] * d2 - Cols[0][3] * d3);
	}

	mat4x4 get_inverse() const
	{
		DType d00 = get_determinant3x3(
				Cols[1][1], Cols[1][2], Cols[1][3], Cols[2][1], Cols[2][2], Cols[2][3],	Cols[3][1], Cols[3][2], Cols[3][3]);
		DType d01 = get_determinant3x3(
				Cols[1][0], Cols[1][2], Cols[1][3],	Cols[2][0], Cols[2][2], Cols[2][3],	Cols[3][0], Cols[3][2], Cols[3][3]);
		DType d02 = get_determinant3x3(
				Cols[1][0], Cols[1][1], Cols[1][3],	Cols[2][0], Cols[2][1], Cols[2][3],	Cols[3][0], Cols[3][1], Cols[3][3]);
		DType d03 = get_determinant3x3(
				Cols[1][0], Cols[1][1], Cols[1][2],	Cols[2][0], Cols[2][1], Cols[2][2],	Cols[3][0], Cols[3][1], Cols[3][2]);

		DType d10 = get_determinant3x3(
				Cols[0][1], Cols[0][2], Cols[0][3], Cols[2][1], Cols[2][2], Cols[2][3], Cols[3][1], Cols[3][2], Cols[3][3]);
		DType d11 = get_determinant3x3(
				Cols[0][0], Cols[0][2], Cols[0][3], Cols[2][0], Cols[2][2], Cols[2][3], Cols[3][0], Cols[3][2], Cols[3][3]);
		DType d12 = get_determinant3x3(
				Cols[0][0], Cols[0][1], Cols[0][3],	Cols[2][0], Cols[2][1], Cols[2][3],	Cols[3][0], Cols[3][1], Cols[3][3]);
		DType d13 = get_determinant3x3(
				Cols[0][0], Cols[0][1], Cols[0][2],	Cols[2][0], Cols[2][1], Cols[2][2],	Cols[3][0], Cols[3][1], Cols[3][2]);

		DType d20 = get_determinant3x3(
				Cols[0][1], Cols[0][2], Cols[0][3], Cols[1][1], Cols[1][2], Cols[1][3], Cols[3][1], Cols[3][2], Cols[3][3]);
		DType d21 = get_determinant3x3(
				Cols[0][0], Cols[0][2], Cols[0][3], Cols[1][0], Cols[1][2], Cols[1][3], Cols[3][0], Cols[3][2], Cols[3][3]);
		DType d22 = get_determinant3x3(
				Cols[0][0], Cols[0][1], Cols[0][3],	Cols[1][0], Cols[1][1], Cols[1][3],	Cols[3][0], Cols[3][1], Cols[3][3]);
		DType d23 = get_determinant3x3(
				Cols[0][0], Cols[0][1], Cols[0][2],	Cols[1][0], Cols[1][1], Cols[1][2],	Cols[3][0], Cols[3][1], Cols[3][2]);

		DType d30 = get_determinant3x3(
				Cols[0][1], Cols[0][2], Cols[0][3], Cols[1][1], Cols[1][2], Cols[1][3], Cols[2][1], Cols[2][2], Cols[2][3]);
		DType d31 = get_determinant3x3(
				Cols[0][0], Cols[0][2], Cols[0][3], Cols[1][0], Cols[1][2], Cols[1][3], Cols[2][0], Cols[2][2], Cols[2][3]);
		DType d32 = get_determinant3x3(
				Cols[0][0], Cols[0][1], Cols[0][3],	Cols[1][0], Cols[1][1], Cols[1][3],	Cols[2][0], Cols[2][1], Cols[2][3]);
		DType d33 = get_determinant3x3(
				Cols[0][0], Cols[0][1], Cols[0][2],	Cols[1][0], Cols[1][1], Cols[1][2],	Cols[2][0], Cols[2][1], Cols[2][2]);

		DType d = Cols[0][0] * d00 - Cols[0][1] * d01 + Cols[0][2] * d02 - Cols[0][3] * d03;
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
				{Cols[0][0], Cols[1][0], Cols[2][0], Cols[3][0]},
				{Cols[0][1], Cols[1][1], Cols[2][1], Cols[3][1]},
				{Cols[0][2], Cols[1][2], Cols[2][2], Cols[3][2]},
				{Cols[0][3], Cols[1][3], Cols[2][3], Cols[3][3]});
		return tMat;
	}

	////////////////////////////////////////
	mat4x4 operator*(const DType scalar) const {
		return mat4x4(
				{Cols[0][0] * scalar, Cols[0][1] * scalar, Cols[0][2] * scalar, Cols[0][3] * scalar},
				{Cols[1][0] * scalar, Cols[1][1] * scalar, Cols[1][2] * scalar, Cols[1][3] * scalar},
				{Cols[2][0] * scalar, Cols[2][1] * scalar, Cols[2][2] * scalar, Cols[2][3] * scalar},
				{Cols[3][0] * scalar, Cols[3][1] * scalar, Cols[3][2] * scalar, Cols[3][3] * scalar});
	}

	mat4x4 operator*(const mat4x4& other) const {
		DType c00 = Cols[0][0] * other[0][0] + Cols[1][0] * other[0][1] + Cols[2][0] * other[0][2] + Cols[3][0] * other[0][3];
		DType c01 = Cols[0][1] * other[0][0] + Cols[1][1] * other[0][1] + Cols[2][1] * other[0][2] + Cols[3][1] * other[0][3];
		DType c02 = Cols[0][2] * other[0][0] + Cols[1][2] * other[0][1] + Cols[2][2] * other[0][2] + Cols[3][2] * other[0][3];
		DType c03 = Cols[0][3] * other[0][0] + Cols[1][3] * other[0][1] + Cols[2][3] * other[0][2] + Cols[3][3] * other[0][3];

		DType c10 = Cols[0][0] * other[1][0] + Cols[1][0] * other[1][1] + Cols[2][0] * other[1][2] + Cols[3][0] * other[1][3];
		DType c11 = Cols[0][1] * other[1][0] + Cols[1][1] * other[1][1] + Cols[2][1] * other[1][2] + Cols[3][1] * other[1][3];
		DType c12 = Cols[0][2] * other[1][0] + Cols[1][2] * other[1][1] + Cols[2][2] * other[1][2] + Cols[3][2] * other[1][3];
		DType c13 = Cols[0][3] * other[1][0] + Cols[1][3] * other[1][1] + Cols[2][3] * other[1][2] + Cols[3][3] * other[1][3];

		DType c20 = Cols[0][0] * other[2][0] + Cols[1][0] * other[2][1] + Cols[2][0] * other[2][2] + Cols[3][0] * other[2][3];
		DType c21 = Cols[0][1] * other[2][0] + Cols[1][1] * other[2][1] + Cols[2][1] * other[2][2] + Cols[3][1] * other[2][3];
		DType c22 = Cols[0][2] * other[2][0] + Cols[1][2] * other[2][1] + Cols[2][2] * other[2][2] + Cols[3][2] * other[2][3];
		DType c23 = Cols[0][3] * other[2][0] + Cols[1][3] * other[2][1] + Cols[2][3] * other[2][2] + Cols[3][3] * other[2][3];

		DType c30 = Cols[0][0] * other[3][0] + Cols[1][0] * other[3][1] + Cols[2][0] * other[3][2] + Cols[3][0] * other[3][3];
		DType c31 = Cols[0][1] * other[3][0] + Cols[1][1] * other[3][1] + Cols[2][1] * other[3][2] + Cols[3][1] * other[3][3];
		DType c32 = Cols[0][2] * other[3][0] + Cols[1][2] * other[3][1] + Cols[2][2] * other[3][2] + Cols[3][2] * other[3][3];
		DType c33 = Cols[0][3] * other[3][0] + Cols[1][3] * other[3][1] + Cols[2][3] * other[3][2] + Cols[3][3] * other[3][3];

		mat4x4 tMat(
				{c00, c01, c02, c03},
				{c10, c11, c12, c13},
				{c20, c21, c22, c23},
				{c30, c31, c32, c33});
		return tMat;
	}

	mat4x4 operator*=(const DType scalar) const {
		Cols[0][0] *= scalar; Cols[0][1] *= scalar; Cols[0][2] *= scalar; Cols[0][3] *= scalar;
		Cols[1][0] *= scalar; Cols[1][1] *= scalar; Cols[1][2] *= scalar; Cols[1][3] *= scalar;
		Cols[2][0] *= scalar; Cols[2][1] *= scalar; Cols[2][2] *= scalar; Cols[2][3] *= scalar;
		Cols[3][0] *= scalar; Cols[3][1] *= scalar; Cols[3][2] *= scalar; Cols[3][3] *= scalar;
		return (*this);
	}

	mat4x4 operator/(const DType scalar) {
		return mat4x4(
				{Cols[0][0] / scalar, Cols[0][1] / scalar, Cols[0][2] / scalar, Cols[0][3] / scalar},
				{Cols[1][0] / scalar, Cols[1][1] / scalar, Cols[1][2] / scalar, Cols[1][3] / scalar},
				{Cols[2][0] / scalar, Cols[2][1] / scalar, Cols[2][2] / scalar, Cols[2][3] / scalar},
				{Cols[3][0] / scalar, Cols[3][1] / scalar, Cols[3][2] / scalar, Cols[3][3] / scalar});
	}

	mat4x4 operator/=(const DType scalar) {
		Cols[0][0] /= scalar; Cols[0][1] /= scalar; Cols[0][2] /= scalar; Cols[0][3] /= scalar;
		Cols[1][0] /= scalar; Cols[1][1] /= scalar; Cols[1][2] /= scalar; Cols[1][3] /= scalar;
		Cols[2][0] /= scalar; Cols[2][1] /= scalar; Cols[2][2] /= scalar; Cols[2][3] /= scalar;
		Cols[3][0] /= scalar; Cols[3][1] /= scalar; Cols[3][2] /= scalar; Cols[3][3] /= scalar;
		return (*this);
	}

	const bool operator==(const mat4x4& other) {
		return (Cols[0][0] == other[0][0] && Cols[0][1] == other[0][1] && Cols[0][2] == other[0][2] && Cols[0][3] == other[0][3] &&
				Cols[1][0] == other[1][0] && Cols[1][1] == other[1][1] && Cols[1][2] == other[1][2] && Cols[1][3] == other[1][3] &&
				Cols[2][0] == other[2][0] && Cols[2][1] == other[2][1] && Cols[2][2] == other[2][2] && Cols[2][3] == other[2][3] &&
				Cols[3][0] == other[3][0] && Cols[3][1] == other[3][1] && Cols[3][2] == other[3][2] && Cols[3][3] == other[3][3]
				);
	}

	ColType& operator[](const u32 colIdx) {
		return Cols[colIdx];
	}

	const ColType& operator[](const u32 colIdx) const {
		return Cols[colIdx];
	}

	//--------------------------------------
	ColType									Cols[4];
	//--------------------------------------
private:
	inline const DType get_determinant3x3(
			DType m00, DType m01, DType m02,
			DType m10, DType m11, DType m12,
			DType m20, DType m21, DType m22) const
	{
		DType d0 = m11 * m22 - m21 * m12;
		DType d1 = m10 * m22 - m20 * m12;
		DType d2 = m10 * m21 - m20 * m11;
		return (m00 * d0 - m01 * d1 + m02 * d2);
	}

};

////////////////////////////////////////////
using mat3x3f = mat3x3<f32>;
using mat3x3i = mat3x3<s32>;
using mat4x4f = mat4x4<f32>;
using mat4x4i = mat4x4<s32>;

////////////////////////////////////////////
// [1;3] x [3;3] = [1;3]
template <class VDType, class MDType>
vec3<VDType> operator*(const vec3<VDType>& v, const mat3x3<MDType>& m) {
	return vec3<VDType>(
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2]
			);
}
// [1;4] x [4;4] = [1;4]
template <class VDType, class MDType>
vec4<VDType> operator*(const vec4<VDType>& v, const mat4x4<MDType>& m) {
	return vec4<VDType>(
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + v.w * m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + v.w * m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + v.w * m[3][2],
			v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + v.w * m[3][3]
			);
}

}

#endif // __FLORAL_MAT_H__
