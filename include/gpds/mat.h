#ifndef __FLORAL_MAT_H__
#define __FLORAL_MAT_H__

#include <stdaliases.h>

#include "vec.h"

namespace floral {
	template <class DType>
	struct mat3x3 {
		explicit mat3x3(const DType val);
		//--------------------------------------
		vec3<DType>								Rows[3];
	};

	template <class DType>
	struct mat4x4 {
		explicit mat4x4(const DType val);
		//--------------------------------------
		vec4<DType>								Rows[4];
	};

	////////////////////////////////////////////
	using mat3x3f = mat3x3<f32>;
	using mat3x3i = mat3x3<s32>;
	using mat4x4f = mat4x4<f32>;
	using mat4x4i = mat4x4<s32>;
}

#endif // __FLORAL_MAT_H__
