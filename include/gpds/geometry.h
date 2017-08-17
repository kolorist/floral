#ifndef __FLORAL_GEOMETRY_H__
#define __FLORAL_GEOMETRY_H__

#include <stdaliases.h>
#include "vec.h"

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

	using ray2df = ray2d<f32>;
	using ray3df = ray3d<f32>;

	////////////////////////////////////////////
	// 2d shape
	struct circle {
	};

	// 3d shape
	template <class ShapeType>
	struct shape3d {
		const bool ray_intersect(const ray3df& r, float *tHit, float *rayEpsilon) {
			return (ShapeType*)(this)->ray_intersect(r, tHit, rayEpsilon);
		}
	};
	
	struct sphere : public shape3d<sphere> {
		const bool ray_intersect(const ray3df& r, float *tHit, float *rayEpsilon);
		//--------------------------------------
		f32 									radius;
		f32 									phiMax;
		f32 									zMin, zMax;
		f32 									thetaMin, thetaMax;
	};

};

#endif // __FLORAL_GEOMETRY_H__
