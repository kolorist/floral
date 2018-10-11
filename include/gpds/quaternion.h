#pragma once

#include <stdaliases.h>

#include "vec.h"
#include "mat.h"

namespace floral {

template <typename t_type>
struct quaternion {
	quaternion()
		: v(0)
		, w(1)
	{ }

	// transfomation
	mat4x4<t_type> to_transform() const {
		vec4<t_type> cv0(1.0f - 2.0f * (v.y * v.y + v.z * v.z), 2.0f * (v.x * v.y - v.z * w), 2.0f * (v.x * v.z + v.y * w), 0.0f);
		vec4<t_type> cv1(2.0f * (v.x * v.y + v.z * w), 1.0f - 2.0f * (v.x * v.x + v.z * v.z), 2.0f * (v.y * v.z - v.x * w), 0.0f);
		vec4<t_type> cv2(2.0f * (v.x * v.z - v.y * w), 2.0f * (v.y * v.z +  v.x * w), 1.0f - 2.0f * (v.x * v.x + v.y * v.y), 0.0f);
		vec4<t_type> cv3(0.0f, 0.0f, 0.0f, 1.0f);
		return mat4x4<t_type>(cv0, cv1, cv2, cv3);
	}

	// inner product
	static t_type dot(const quaternion& q1, const quaternion& q2) {
		return (vec3::dot(q1.v, q2.v) + q1.w * q2.w);
	}

	quaternion normalize() {
		return (*this) / sqrt(dot(*this, *this));
	}

	// -----------------------------------------
	vec3<t_type>								v;
	t_type										w;
};

// ---------------------------------------------
using quaternionf = quaternion<f32>;

// ---------------------------------------------
template <typename t_type>
quaternion<t_type> operator*(const quaternion<t_type>& q1, const quaternion<t_type>& q2){
	quaternion<t_type> retQuat;
	retQuat.v = cross(q1.v, q2.v) + q1.w * q2.v + q2.w * q1.v;
	retQuat.w = q1.w * q2.w - dot(q1.v, q2.v);
	return retQuat;
}

template <typename t_type>
quaternion<t_type> operator-(const quaternion<t_type>& q1, const quaternion<t_type>& q2) {
	quaternion<t_type> retQuat;
	retQuat.v = q1.v - q2.v;
	retQuat.w = q1.w - q2.w;
	return retQuat;
}

template <typename t_type>
quaternion<t_type> operator+(const quaternion<t_type>& q1, const quaternion<t_type>& q2) {
	quaternion<t_type> retQuat;
	retQuat.v = q1.v + q2.v;
	retQuat.w = q1.w + q2.w;
	return retQuat;
}

template <class t_type>
quaternion<t_type> operator*(const f32 i_scalar, const quaternion<t_type>& i_q) {
	quaternion<t_type> retQuat;
	retQuat.v = i_scalar * i_q.v;
	retQuat.w = i_scalar * i_q.w;
	return retQuat;
}

template <class t_type>
quaternion<t_type> operator/(const f32 i_scalar, const quaternion<t_type>& i_q) {
	quaternion<t_type> retQuat;
	retQuat.v = i_scalar / i_q.v;
	retQuat.w = i_scalar / i_q.w;
	return retQuat;
}

}
