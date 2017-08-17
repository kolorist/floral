#ifndef __FLORAL_MAT_H__
#define __FLORAL_MAT_H__

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

		explicit mat3x3(const DType val)
		{
			memset(Rows, 0, sizeof(Rows));
			Rows[0][0] = val;
			Rows[1][1] = val;
			Rows[2][2] = val;
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
		explicit mat4x4(const DType val);
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
}

#endif // __FLORAL_MAT_H__
