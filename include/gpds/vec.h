#ifndef __FLORAL_VEC_H__
#define __FLORAL_VEC_H__

namespace floral {
	template <class DType>
	struct vec2 {
		DType 									x, y;
	};

	template <class DType>
	struct vec3 {
		DType 									x, y, z;
	};

	template <class DType>
	struct vec4 {
		DType									x, y, z, w;
	};
};

#endif // __FLORAL_VEC_H__
