#ifndef __FLORAL_RECT_H__
#define __FLORAL_RECT_H__

#include <stdaliases.h>

#include "vec.h"

// TODO: contains rect (in 2D) and bbox (in 3D), rect.h? it's a stupid name, yes, i know

namespace floral {
	/*---Rectangle---*/
	template <class DType>
	struct rect {
		rect()
		{ }

		rect(const vec2<DType>& topLeft, const vec2<DType>& bottomRight)
			: top_left(topLeft)
			, bottom_right(bottomRight)
			, width(bottomRight.x - topLeft.x)
			, height(topLeft.y - bottomRight.y)
		{ }
		
		rect(const vec2<DType>& topLeft, const DType& w, const DType& h)
			: top_left(topLeft)
			, bottom_right(topLeft.x + w, topLeft.y - h)
			, width(w)
			, height(h)
		{ }

		vec2<DType>								top_left;
		vec2<DType>								bottom_right;
		DType									width;
		DType									height;
	};

	/*---Axis Aligned Bounding Box---*/
	template <class DType>
	struct aabb {
		aabb()
		{ }

		aabb(const aabb& other)
			: min_corner(other.min_corner)
			, max_corner(other.max_corner)
		{ }

		aabb(const vec3<DType>& v0, const vec3<DType>& v1)
			: min_corner(v0)
			, max_corner(v1)
		{ }

		vec3<DType>								min_corner;
		vec3<DType>								max_corner;
	};

	/*---Oriented Bounding Box---*/
	template <class DType>
	struct obb {
	};

	using rect2f = rect<f32>;
	using rect2i = rect<s32>;

	using aabb3f = aabb<f32>;
}

#endif // __FLORAL_RECT_H__
