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

	};

	/*---Oriented Bounding Box---*/
	template <class DType>
	struct obb {
	};

	using rect2f = rect<f32>;
	using rect2i = rect<s32>;
}

#endif // __FLORAL_RECT_H__
