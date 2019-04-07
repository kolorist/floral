#pragma once

#include "floral/stdaliases.h"

#include <math.h>

namespace floral {

template <class t_type>
struct vec2 {
	vec2()										: x(0), y(0) {}
	explicit vec2(const t_type i_val)			: x(i_val), y(i_val) {}
	vec2(const vec2& i_other)					: x(i_other.x), y(i_other.y) {}
	vec2(const t_type i_x, const t_type i_y)	: x(i_x), y(i_y) {}

	// assignment
	vec2& operator=(const vec2& i_other) {
		x = i_other.x;
		y = i_other.y;
		return (*this);
	}
	
	vec2& operator+=(const vec2& i_other) {
		x += i_other.x;
		y += i_other.y;
		return (*this);
	}

	vec2& operator-=(const vec2& i_other) {
		x -= i_other.x;
		y -= i_other.y;
		return (*this);
	}

	vec2& operator*=(const vec2& i_other) {
		x *= i_other.x;
		y *= i_other.y;
		return (*this);
	}

	vec2& operator*=(const t_type i_scalar) {
		x *= i_scalar;
		y *= i_scalar;
		return (*this);
	}

	vec2& operator/=(const vec2& i_other) {
		x /= i_other.x;
		y /= i_other.y;
		return (*this);
	}

	vec2& operator/=(const t_type i_scalar) {
		x /= i_scalar;
		y /= i_scalar;
		return (*this);
	}

	// self modifications
	vec2 normalize() {
		f32 len = sqrtf(x * x + y * y);
		x /= len;
		y /= len;
		return vec2(x, y);
	}
	
	//--------------------------------------
	t_type 									x, y;
};

// ---------------------------------------------
// comparison
template <typename t_type> bool operator==(const vec2<t_type>& i_a, const vec2<t_type>& i_b) {
	return (i_a.x == i_b.x && i_a.y == i_b.y);
}

// component-wise arithmetic
template <typename t_type> vec2<t_type> operator+(const vec2<t_type>& i_a) {
	return vec2<t_type>(i_a.x, i_a.y);
}

template <typename t_type> vec2<t_type> operator-(const vec2<t_type>& i_a) {
	return vec2<t_type>(-i_a.x, -i_a.y);
}

template <typename t_type> vec2<t_type> operator+(const vec2<t_type>& i_a, const vec2<t_type>& i_b) {
	return vec2<t_type>(i_a.x + i_b.x, i_a.y + i_b.y);
}

template <typename t_type> vec2<t_type> operator-(const vec2<t_type>& i_a, const vec2<t_type>& i_b) {
	return vec2<t_type>(i_a.x - i_b.x, i_a.y - i_b.y);
}

template <typename t_type> vec2<t_type> operator*(const vec2<t_type>& i_a, const vec2<t_type>& i_b) {
	return vec2<t_type>(i_a.x * i_b.x, i_a.y * i_b.y);
}

template <typename t_type> vec2<t_type> operator/(const vec2<t_type>& i_a, const vec2<t_type>& i_b) {
	return vec2<t_type>(i_a.x / i_b.x, i_a.y / i_b.y);
}

// scalar arithmetic
template <typename t_type> vec2<t_type> operator*(const vec2<t_type>& i_a, const t_type i_scalar) {
	return vec2<t_type>(i_a.x * i_scalar, i_a.y * i_scalar);
}

template <typename t_type> vec2<t_type> operator*(const t_type i_scalar, const vec2<t_type>& i_a) {
	return vec2<t_type>(i_a.x * i_scalar, i_a.y * i_scalar);
}

template <typename t_type> vec2<t_type> operator/(const vec2<t_type>& i_a, const t_type i_scalar) {
	return vec2<t_type>(i_a.x / i_scalar, i_a.y / i_scalar);
}

template <typename t_type> vec2<t_type> operator/(const t_type i_scalar, const vec2<t_type>& i_a) {
	return vec2<t_type>(i_scalar / i_a.x, i_scalar / i_a.y);
}

// vector arithmetic
template <typename t_type> const t_type dot(const vec2<t_type>& i_a, const vec2<t_type>& i_b) {
	return (i_a.x * i_b.x + i_a.y * i_b.y);
}

template <typename t_type> const f32 length(const vec2<t_type>& i_a) {
	return sqrtf(i_a.x * i_a.x + i_a.y * i_a.y);
}

template <typename t_type> const vec2<t_type> normalize(const vec2<t_type>& i_a) {
	f32 len = length(i_a);
	return vec2<t_type>(i_a.x / len, i_a.y / len);
}
// ---------------------------------------------

template <class t_type>
struct vec3 {
	vec3()										: x(0), y(0), z(0) {}
	explicit vec3(const t_type i_val)			: x(i_val), y(i_val), z(i_val) {}
	vec3(const vec3& i_other)					: x(i_other.x), y(i_other.y), z(i_other.z) {}
	vec3(const t_type i_x, const t_type i_y, const t_type i_z) : x(i_x), y(i_y), z(i_z) {}

	// assignment
	vec3& operator=(const vec3& i_other) {
		x = i_other.x;
		y = i_other.y;
		z = i_other.z;
		return (*this);
	}

	vec3& operator+=(const vec3& i_other) {
		x += i_other.x;
		y += i_other.y;
		z += i_other.z;
		return (*this);
	}

	vec3& operator-=(const vec3& i_other) {
		x -= i_other.x;
		y -= i_other.y;
		z -= i_other.z;
		return (*this);
	}

	vec3& operator*=(const vec3& i_other) {
		x *= i_other.x;
		y *= i_other.y;
		z *= i_other.z;
		return (*this);
	}

	vec3& operator*=(const t_type i_scalar) {
		x *= i_scalar;
		y *= i_scalar;
		z *= i_scalar;
		return (*this);
	}

	vec3& operator/=(const vec3& i_other) {
		x /= i_other.x;
		y /= i_other.y;
		z /= i_other.z;
		return (*this);
	}

	vec3& operator/=(const t_type i_scalar) {
		x /= i_scalar;
		y /= i_scalar;
		z /= i_scalar;
		return (*this);
	}

	// self modifications
	vec3 normalize() {
		f32 len = sqrtf(x * x + y * y + z * z);
		x /= len;
		y /= len;
		z /= len;
		return vec3(x, y, z);
	}
	
	//--------------------------------------
	t_type 									x, y, z;
};

// ---------------------------------------------
// comparison
template <typename t_type> bool operator==(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	return (i_a.x == i_b.x && i_a.y == i_b.y && i_a.z == i_b.z);
}

// component-wise arithmetic
template <typename t_type> vec3<t_type> operator+(const vec3<t_type>& i_a) {
	return vec3<t_type>(i_a.x, i_a.y, i_a.z);
}

template <typename t_type> vec3<t_type> operator-(const vec3<t_type>& i_a) {
	return vec3<t_type>(-i_a.x, -i_a.y, -i_a.z);
}

template <typename t_type> vec3<t_type> operator+(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	return vec3<t_type>(i_a.x + i_b.x, i_a.y + i_b.y, i_a.z + i_b.z);
}

template <typename t_type> vec3<t_type> operator-(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	return vec3<t_type>(i_a.x - i_b.x, i_a.y - i_b.y, i_a.z - i_b.z);
}

template <typename t_type> vec3<t_type> operator*(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	return vec3<t_type>(i_a.x * i_b.x, i_a.y * i_b.y, i_a.z * i_b.z);
}

template <typename t_type> vec3<t_type> operator/(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	return vec3<t_type>(i_a.x / i_b.x, i_a.y / i_b.y, i_a.z / i_b.z);
}

// scalar arithmetic
template <typename t_type> vec3<t_type> operator*(const vec3<t_type>& i_a, const t_type i_scalar) {
	return vec3<t_type>(i_a.x * i_scalar, i_a.y * i_scalar, i_a.z * i_scalar);
}

template <typename t_type> vec3<t_type> operator*(const t_type i_scalar, const vec3<t_type>& i_a) {
	return vec3<t_type>(i_a.x * i_scalar, i_a.y * i_scalar, i_a.z * i_scalar);
}

template <typename t_type> vec3<t_type> operator/(const vec3<t_type>& i_a, const t_type i_scalar) {
	return vec3<t_type>(i_a.x / i_scalar, i_a.y / i_scalar, i_a.z / i_scalar);
}

template <typename t_type> vec3<t_type> operator/(const t_type i_scalar, const vec3<t_type>& i_a) {
	return vec3<t_type>(i_scalar / i_a.x, i_scalar / i_a.y, i_scalar / i_a.z);
}

// vector arithmetic
template <typename t_type> const t_type dot(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	return (i_a.x * i_b.x + i_a.y * i_b.y + i_a.z * i_b.z);
}

template <typename t_type> const vec3<t_type> cross(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	return vec3<t_type>(
			i_a.y * i_b.z - i_a.z * i_b.y,
			i_a.z * i_b.x - i_a.x * i_b.z,
			i_a.x * i_b.y - i_a.y * i_b.x);
}

template <typename t_type> const f32 length(const vec3<t_type>& i_a) {
	return sqrtf(i_a.x * i_a.x + i_a.y * i_a.y + i_a.z * i_a.z);
}

template <typename t_type> const vec3<t_type> normalize(const vec3<t_type>& i_a) {
	f32 len = length(i_a);
	return vec3<t_type>(i_a.x / len, i_a.y / len, i_a.z / len);
}
// ---------------------------------------------

template <class t_type>
struct vec4 {
	vec4()										: x(0), y(0), z(0), w(0) {}
	vec4(const t_type i_val)					: x(i_val), y(i_val), z(i_val), w(i_val) {}
	vec4(const vec4& i_other)					: x(i_other.x), y(i_other.y), z(i_other.z), w(i_other.w) {}
	vec4(const t_type i_x, const t_type i_y, const t_type i_z, const t_type i_w) : x(i_x), y(i_y), z(i_z), w(i_w) {}
	vec4(const vec3<t_type>& i_other, const t_type i_w) : x(i_other.x), y(i_other.y), z(i_other.z), w(i_w) {}

	// assignment
	vec4& operator=(const vec4& i_other) {
		x = i_other.x;
		y = i_other.y;
		z = i_other.z;
		w = i_other.w;
		return (*this);
	}
	
	vec4& operator+=(const vec4& i_other) {
		x += i_other.x;
		y += i_other.y;
		z += i_other.z;
		w += i_other.w;
		return (*this);
	}

	vec4& operator-=(const vec4& i_other) {
		x -= i_other.x;
		y -= i_other.y;
		z -= i_other.z;
		w -= i_other.w;
		return (*this);
	}

	vec4& operator*=(const vec4& i_other) {
		x *= i_other.x;
		y *= i_other.y;
		z *= i_other.z;
		w *= i_other.w;
		return (*this);
	}

	vec4& operator*=(const t_type i_scalar) {
		x *= i_scalar;
		y *= i_scalar;
		z *= i_scalar;
		w *= i_scalar;
		return (*this);
	}

	vec4& operator/=(const vec4& i_other) {
		x /= i_other.x;
		y /= i_other.y;
		z /= i_other.z;
		w /= i_other.w;
		return (*this);
	}

	vec4& operator/=(const t_type i_scalar) {
		x /= i_scalar;
		y /= i_scalar;
		z /= i_scalar;
		w /= i_scalar;
		return (*this);
	}

	// self modifications
	vec4 normalize() {
		f32 len = sqrtf(x * x + y * y + z * z + w * w);
		x /= len;
		y /= len;
		z /= len;
		w /= len;
		return vec4(x, y, z, w);
	}
	
	
	//--------------------------------------
	t_type									x, y, z, w;
};

// ---------------------------------------------
// comparison
template <typename t_type> bool operator==(const vec4<t_type>& i_a, const vec4<t_type>& i_b) {
	return (i_a.x == i_b.x && i_a.y == i_b.y && i_a.z == i_b.z && i_a.w == i_b.w);
}

// component-wise arithmetic
template <typename t_type> vec4<t_type> operator+(const vec4<t_type>& i_a) {
	return vec4<t_type>(i_a.x, i_a.y, i_a.z, i_a.w);
}

template <typename t_type> vec4<t_type> operator-(const vec4<t_type>& i_a) {
	return vec4<t_type>(-i_a.x, -i_a.y, -i_a.z, -i_a.w);
}

template <typename t_type> vec4<t_type> operator+(const vec4<t_type>& i_a, const vec4<t_type>& i_b) {
	return vec4<t_type>(i_a.x + i_b.x, i_a.y + i_b.y, i_a.z + i_b.z, i_a.w + i_b.w);
}

template <typename t_type> vec4<t_type> operator-(const vec4<t_type>& i_a, const vec4<t_type>& i_b) {
	return vec4<t_type>(i_a.x - i_b.x, i_a.y - i_b.y, i_a.z - i_b.z, i_a.w - i_b.w);
}

template <typename t_type> vec4<t_type> operator*(const vec4<t_type>& i_a, const vec4<t_type>& i_b) {
	return vec4<t_type>(i_a.x * i_b.x, i_a.y * i_b.y, i_a.z * i_b.z, i_a.w * i_b.w);
}

template <typename t_type> vec4<t_type> operator/(const vec4<t_type>& i_a, const vec4<t_type>& i_b) {
	return vec4<t_type>(i_a.x / i_b.x, i_a.y / i_b.y, i_a.z / i_b.z, i_a.w / i_b.w);
}

// scalar arithmetic
template <typename t_type> vec4<t_type> operator*(const vec4<t_type>& i_a, const t_type i_scalar) {
	return vec4<t_type>(i_a.x * i_scalar, i_a.y * i_scalar, i_a.z * i_scalar, i_a.w * i_scalar);
}

template <typename t_type> vec4<t_type> operator*(const t_type i_scalar, const vec4<t_type>& i_a) {
	return vec4<t_type>(i_a.x * i_scalar, i_a.y * i_scalar, i_a.z * i_scalar, i_a.w * i_scalar);
}

template <typename t_type> vec4<t_type> operator/(const vec4<t_type>& i_a, const t_type i_scalar) {
	return vec4<t_type>(i_a.x / i_scalar, i_a.y / i_scalar, i_a.z / i_scalar, i_a.w / i_scalar);
}

template <typename t_type> vec4<t_type> operator/(const t_type i_scalar, const vec4<t_type>& i_a) {
	return vec4<t_type>(i_scalar / i_a.x, i_scalar / i_a.y, i_scalar / i_a.z, i_scalar / i_a.w);
}

// vector arithmetic
template <typename t_type> const t_type dot(const vec4<t_type>& i_a, const vec4<t_type>& i_b) {
	return (i_a.x * i_b.x + i_a.y * i_b.y + i_a.z * i_b.z + i_a.w * i_b.w);
}

template <typename t_type> const f32 length(const vec4<t_type>& i_a) {
	return sqrtf(i_a.x * i_a.x + i_a.y * i_a.y + i_a.z * i_a.z + i_a.w * i_a.w);
}

template <typename t_type> const vec4<t_type> normalize(const vec4<t_type>& i_a) {
	f32 len = length(i_a);
	return vec4<t_type>(i_a.x / len, i_a.y / len, i_a.z / len, i_a.w / len);
}

template <typename t_type> const f32 angle(const vec3<t_type>& i_a, const vec3<t_type>& i_b) {
	vec3<t_type> na = normalize(i_a);
	vec3<t_type> nb = normalize(i_b);
	f32 cosTheta = dot(na, nb);
	return acosf(cosTheta);
}

// ---------------------------------------------
using vec2f = vec2<f32>;
using vec2i = vec2<s32>;
using vec3f = vec3<f32>;
using vec3i = vec3<s32>;
using vec4f = vec4<f32>;
using vec4i = vec4<s32>;

};