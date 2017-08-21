#ifndef __FLORAL_MAT_H__
#define __FLORAL_MAT_H__

#include <cstring>

#include <stdaliases.h>

#include "vec.h"

namespace floral {
	template <class DType>
	struct mat3x3 {
		typedef DType							RowType[3];

		mat3x3()
		{
			memset(Rows, 0, sizeof(Rows));
		}

		mat3x3(const vec3<DType>& r1, const vec3<DType>& r2, const vec3<DType>& r3)
		{
			Rows[0][0] = r1.x; Rows[0][1] = r1.y; Rows[0][2] = r1.z;
			Rows[1][0] = r2.x; Rows[1][1] = r2.y; Rows[1][2] = r2.z;
			Rows[2][0] = r3.x; Rows[2][1] = r3.y; Rows[2][2] = r3.z;
		}

		// noone should do this, this is ridiculous -.-!
		mat3x3(RowType rows[])
		{
			Rows[0][0] = rows[0][0]; Rows[0][1] = rows[0][1]; Rows[0][2] = m02;
			Rows[1][0] = rows[1][0]; Rows[1][1] = rows[1][1]; Rows[1][2] = m12;
			Rows[2][0] = rows[2][0]; Rows[2][1] = rows[2][1]; Rows[2][2] = m22;
		}

		explicit mat3x3(const DType val)
		{
			memset(Rows, 0, sizeof(Rows));
			Rows[0][0] = val;
			Rows[1][1] = val;
			Rows[2][2] = val;
		}

		////////////////////////////////////////
		const DType get_determinant() const 
		{
			return (Rows[0][0] * (Rows[1][1] * Rows [2][2] - Rows[2][1] * Rows[1][2])
					- Rows[0][1] * (Rows[1][0] * Rows[2][2] - Rows[2][0] * Rows[1][2])
					+ Rows[0][2] * (Rows[1][0] * Rows[2][1] - Rows[2][0] * Rows[1][1]));
		}

		////////////////////////////////////////

		const bool operator==(const mat3x3& other) {
			return (Rows[0][0] == other[0][0] && Rows[0][1] == other[0][1] && Rows[0][2] == other[0][2] &&
					Rows[1][0] == other[1][0] && Rows[1][1] == other[1][1] && Rows[1][2] == other[1][2] &&
					Rows[2][0] == other[2][0] && Rows[2][1] == other[2][1] && Rows[2][2] == other[2][2]);
		}

		RowType& operator[](const u32 rowIdx) {
			return Rows[rowIdx];
		}

		const RowType& operator[](const u32 rowIdx) const {
			return Rows[rowIdx];
		}

		//--------------------------------------
		RowType									Rows[3];
	};

	template <class DType>
	struct mat4x4 {
		typedef DType							RowType[4];

		mat4x4()
		{
			memset(Rows, 0, sizeof(Rows));
		}

		mat4x4(const vec4<DType>& r1, const vec4<DType>& r2, const vec4<DType>& r3, const vec4<DType>& r4)
		{
			Rows[0][0] = r1.x; Rows[0][1] = r1.y; Rows[0][2] = r1.z; Rows[0][3] = r1.w;
			Rows[1][0] = r2.x; Rows[1][1] = r2.y; Rows[1][2] = r2.z; Rows[1][3] = r2.w;
			Rows[2][0] = r3.x; Rows[2][1] = r3.y; Rows[2][2] = r3.z; Rows[2][3] = r3.w;
			Rows[3][0] = r4.x; Rows[3][1] = r4.y; Rows[3][2] = r4.z; Rows[3][3] = r4.w;
		}

		explicit mat4x4(const DType val)
		{
			memset(Rows, 0, sizeof(Rows));
			Rows[0][0] = val;
			Rows[1][1] = val;
			Rows[2][2] = val;
			Rows[3][3] = val;
		}
		
		////////////////////////////////////////
		const DType get_determinant() const
		{
			DType d00 = Rows[2][2] * Rows[3][3] - Rows[3][2] * Rows[2][3];
			DType d01 = Rows[2][1] * Rows[3][3] - Rows[3][1] * Rows[2][3]; // d10
			DType d02 = Rows[2][1] * Rows[3][2] - Rows[3][2] * Rows[2][2];
			DType d11 = Rows[2][0] * Rows[3][3] - Rows[3][0] * Rows[2][3];
			DType d12 = Rows[2][0] * Rows[2][3] - Rows[3][0] * Rows[2][2];

			DType d0;
			DType d1;
			DType d2;
			DType d3;
		}

		////////////////////////////////////////

		const bool operator==(const mat4x4& other) {
			return (Rows[0][0] == other[0][0] && Rows[0][1] == other[0][1] && Rows[0][2] == other[0][2] && Rows[0][3] == other[0][3] &&
					Rows[1][0] == other[1][0] && Rows[1][1] == other[1][1] && Rows[1][2] == other[1][2] && Rows[1][3] == other[1][3] &&
					Rows[2][0] == other[2][0] && Rows[2][1] == other[2][1] && Rows[2][2] == other[2][2] && Rows[2][3] == other[2][3] &&
					Rows[3][0] == other[3][0] && Rows[3][1] == other[3][1] && Rows[3][2] == other[3][2] && Rows[3][3] == other[3][3]
					);
		}

		RowType& operator[](const u32 rowIdx) {
			return Rows[rowIdx];
		}

		const RowType& operator[](const u32 rowIdx) const {
			return Rows[rowIdx];
		}

		//--------------------------------------
		RowType									Rows[4];
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
				v.x * m[0][0] + v.x * m[1][0] + v.x * m[2][0],
				v.y * m[0][1] + v.y * m[1][1] + v.y * m[2][1],
				v.z * m[0][2] + v.z * m[1][2] + v.z * m[2][2]
				);
	}
	// [1;4] x [4;4] = [1;4]
	template <class VDType, class MDType>
	vec4<VDType> operator*(const vec4<VDType>& v, const mat4x4<MDType>& m) {
		return vec4<VDType>(
				v.x * m[0][0] + v.x * m[1][0] + v.x * m[2][0] + v.w * m[3][0],
				v.y * m[0][1] + v.y * m[1][1] + v.y * m[2][1] + v.w * m[3][1],
				v.z * m[0][2] + v.z * m[1][2] + v.z * m[2][2] + v.w * m[3][2],
				v.z * m[0][3] + v.z * m[1][3] + v.z * m[2][3] + v.w * m[3][3]
				);
	}
	// [3;3] x [3;3] = [3;3]
	template <class DType>
	mat3x3<DType> operator*(const mat3x3<DType>& lhs, const mat3x3<DType>& rhs) {
		vec3<DType> r1(lhs[0][0], lhs[0][1], lhs[0][2]);
		vec3<DType> r2(lhs[1][0], lhs[1][1], lhs[1][2]);
		vec3<DType> r3(lhs[2][0], lhs[2][1], lhs[2][2]);
		return mat3x3<DType>(
					r1 * rhs,
					r2 * rhs,
					r3 * rhs);
	}
	// [4;4] x [4;4] = [4;4]
	template <class DType>
	mat4x4<DType> operator*(const mat4x4<DType>& lhs, const mat4x4<DType>& rhs) {
		vec4<DType> r1(lhs[0][0], lhs[0][1], lhs[0][2], lhs[0][3]);
		vec4<DType> r2(lhs[1][0], lhs[1][1], lhs[1][2], lhs[1][3]);
		vec4<DType> r3(lhs[2][0], lhs[2][1], lhs[2][2], lhs[2][3]);
		vec4<DType> r4(lhs[3][0], lhs[3][1], lhs[3][2], lhs[3][3]);
		return mat4x4<DType>(
					r1 * rhs,
					r2 * rhs,
					r3 * rhs,
					r4 * rhs);
	}
}

#endif // __FLORAL_MAT_H__
