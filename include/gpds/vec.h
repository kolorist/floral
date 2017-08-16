#ifndef __FLORAL_VEC_H__
#define __FLORAL_VEC_H__

#include <stdaliases.h>

namespace floral {
	/*---Point---*/
	template <class DType>
	struct point2d {
		DType									x, y;
	};

	template <class DType>
	struct point3d {
		DType									x, y, z;
	};

	/*---Vector---*/
	template <class DType>
	struct vec2 {
		vec2()
			: x(0), y(0)
		{}

		explicit vec2(const DType val)
			: x(val), y(val)
		{}
		
		vec2(const vec2& other)
			: x(other.x), y(other.y)
		{}

		vec2(const DType xVal, const DType yVal)
			: x(xVal), y(yVal)
		{}
		// arthimetic: add, sub
		vec2& operator+=(const vec2& other) {
			x += other.x;
			y += other.y;
			return (*this);
		}

		vec2 operator+(const vec2& other) {
			return vec2(x + other.x, y + other.y);
		}
		// scaling: mul, div, invert
		// dot and cross
		// normalize
		//--------------------------------------
		DType 									x, y;
	};

	template <class DType>
	struct vec3 {
		//--------------------------------------
		DType 									x, y, z;
	};

	template <class DType>
	struct vec4 {
		//--------------------------------------
		DType									x, y, z, w;
	};

	/*---Ray---*/
	template <class DType>
	struct ray2d {
		//--------------------------------------
		point2d<DType>							o;
		vec2<DType>								d;
	};

	template <class DType>
	struct ray3d {
		//--------------------------------------
		point3d<DType>							o;
		vec3<DType>								d;
	};

	////////////////////////////////////////////
	using point2df = point2d<f32>;
	using point2di = point2d<s32>;
	using point3df = point3d<f32>;
	using point3di = point3d<s32>;

	using vec2f = vec2<f32>;
	using vec2i = vec2<s32>;
	using vec3f = vec3<f32>;
	using vec3i = vec3<s32>;
	using vec4f = vec4<f32>;
	using vec4i = vec4<s32>;

	using ray2df = ray2d<f32>;
	using ray3df = ray3d<f32>;
};

#endif // __FLORAL_VEC_H__
