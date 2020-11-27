#pragma once

#include "floral/stdaliases.h"

#include <cmath>

namespace floral
{
// ----------------------------------------------------------------------------

template <class t_type>
struct vec2
{
	vec2()										: x(0), y(0) {}
	explicit vec2(const t_type val)				: x(val), y(val) {}
	vec2(const vec2& other)						: x(other.x), y(other.y) {}
	vec2(const t_type x, const t_type y)		: x(x), y(y) {}

	// assignment
	vec2& operator=(const vec2& other)
	{
		x = other.x;
		y = other.y;
		return (*this);
	}
	
	vec2& operator+=(const vec2& other)
	{
		x += other.x;
		y += other.y;
		return (*this);
	}

	vec2& operator-=(const vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return (*this);
	}

	vec2& operator*=(const vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return (*this);
	}

	vec2& operator*=(const t_type scalar)
	{
		x *= scalar;
		y *= scalar;
		return (*this);
	}

	vec2& operator/=(const vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return (*this);
	}

	vec2& operator/=(const t_type scalar)
	{
		x /= scalar;
		y /= scalar;
		return (*this);
	}

	// self modifications
	vec2 normalize()
	{
		f32 len = sqrtf(x * x + y * y);
		x /= len;
		y /= len;
		return vec2(x, y);
	}
	
	t_type 									x, y;
};

// ----------------------------------------------------------------------------
// comparison
template <typename t_type>
inline bool operator==(const vec2<t_type>& a, const vec2<t_type>& b)
{
	return (a.x == b.x && a.y == b.y);
}

// component-wise arithmetic
template <typename t_type>
inline vec2<t_type> operator+(const vec2<t_type>& a)
{
	return vec2<t_type>(a.x, a.y);
}

template <typename t_type>
inline vec2<t_type> operator-(const vec2<t_type>& a)
{
	return vec2<t_type>(-a.x, -a.y);
}

template <typename t_type> vec2<t_type>
inline operator+(const vec2<t_type>& a, const vec2<t_type>& b)
{
	return vec2<t_type>(a.x + b.x, a.y + b.y);
}

template <typename t_type> vec2<t_type> operator-(const vec2<t_type>& a, const vec2<t_type>& b) {
	return vec2<t_type>(a.x - b.x, a.y - b.y);
}

template <typename t_type> vec2<t_type> operator*(const vec2<t_type>& a, const vec2<t_type>& b) {
	return vec2<t_type>(a.x * b.x, a.y * b.y);
}

template <typename t_type> vec2<t_type> operator/(const vec2<t_type>& a, const vec2<t_type>& b) {
	return vec2<t_type>(a.x / b.x, a.y / b.y);
}

// scalar arithmetic
template <typename t_type> vec2<t_type> operator*(const vec2<t_type>& a, const t_type scalar) {
	return vec2<t_type>(a.x * scalar, a.y * scalar);
}

template <typename t_type> vec2<t_type> operator*(const t_type scalar, const vec2<t_type>& a) {
	return vec2<t_type>(a.x * scalar, a.y * scalar);
}

template <typename t_type> vec2<t_type> operator/(const vec2<t_type>& a, const t_type scalar) {
	return vec2<t_type>(a.x / scalar, a.y / scalar);
}

template <typename t_type> vec2<t_type> operator/(const t_type scalar, const vec2<t_type>& a) {
	return vec2<t_type>(scalar / a.x, scalar / a.y);
}

// vector arithmetic
template <typename t_type> const t_type dot(const vec2<t_type>& a, const vec2<t_type>& b) {
	return (a.x * b.x + a.y * b.y);
}

template <typename t_type> const t_type length(const vec2<t_type>& a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

template <typename t_type> const vec2<t_type> normalize(const vec2<t_type>& a) {
	f32 len = length(a);
	return vec2<t_type>(a.x / len, a.y / len);
}

template <typename t_type> const bool equal(const vec2<t_type>& a, const vec2<t_type>& b, const f32 epsilon) {
	f32 disp = length(a - b);
	return (disp < epsilon);
}
// ---------------------------------------------

template <class t_type>
struct vec3 {
	vec3()										: x(0), y(0), z(0) {}
	explicit vec3(const t_type val)			: x(val), y(val), z(val) {}
	vec3(const vec3& other)					: x(other.x), y(other.y), z(other.z) {}
	vec3(const t_type x, const t_type y, const t_type z) : x(x), y(y), z(z) {}

	// assignment
	vec3& operator=(const vec3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return (*this);
	}

	vec3& operator+=(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return (*this);
	}

	vec3& operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return (*this);
	}

	vec3& operator*=(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return (*this);
	}

	vec3& operator*=(const t_type scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return (*this);
	}

	vec3& operator/=(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return (*this);
	}

	vec3& operator/=(const t_type scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
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
template <typename t_type> bool operator==(const vec3<t_type>& a, const vec3<t_type>& b) {
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

// component-wise arithmetic
template <typename t_type> vec3<t_type> operator+(const vec3<t_type>& a) {
	return vec3<t_type>(a.x, a.y, a.z);
}

template <typename t_type> vec3<t_type> operator-(const vec3<t_type>& a) {
	return vec3<t_type>(-a.x, -a.y, -a.z);
}

template <typename t_type> vec3<t_type> operator+(const vec3<t_type>& a, const vec3<t_type>& b) {
	return vec3<t_type>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename t_type> vec3<t_type> operator-(const vec3<t_type>& a, const vec3<t_type>& b) {
	return vec3<t_type>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <typename t_type> vec3<t_type> operator*(const vec3<t_type>& a, const vec3<t_type>& b) {
	return vec3<t_type>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template <typename t_type> vec3<t_type> operator/(const vec3<t_type>& a, const vec3<t_type>& b) {
	return vec3<t_type>(a.x / b.x, a.y / b.y, a.z / b.z);
}

// scalar arithmetic
template <typename t_type> vec3<t_type> operator*(const vec3<t_type>& a, const t_type scalar) {
	return vec3<t_type>(a.x * scalar, a.y * scalar, a.z * scalar);
}

template <typename t_type> vec3<t_type> operator*(const t_type scalar, const vec3<t_type>& a) {
	return vec3<t_type>(a.x * scalar, a.y * scalar, a.z * scalar);
}

template <typename t_type> vec3<t_type> operator/(const vec3<t_type>& a, const t_type scalar) {
	return vec3<t_type>(a.x / scalar, a.y / scalar, a.z / scalar);
}

template <typename t_type> vec3<t_type> operator/(const t_type scalar, const vec3<t_type>& a) {
	return vec3<t_type>(scalar / a.x, scalar / a.y, scalar / a.z);
}

// vector arithmetic
template <typename t_type> const t_type dot(const vec3<t_type>& a, const vec3<t_type>& b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

template <typename t_type> const vec3<t_type> cross(const vec3<t_type>& a, const vec3<t_type>& b) {
	return vec3<t_type>(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
}

template <typename t_type> const t_type length(const vec3<t_type>& a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

template <typename t_type> const vec3<t_type> normalize(const vec3<t_type>& a) {
	t_type len = length(a);
	return vec3<t_type>(a.x / len, a.y / len, a.z / len);
}

template <typename t_type> const bool equal(const vec3<t_type>& a, const vec3<t_type>& b, const f32 epsilon) {
	f32 disp = length(a - b);
	return (disp < epsilon);
}
// ---------------------------------------------

template <class t_type>
struct vec4 {
	vec4()										: x(0), y(0), z(0), w(0) {}
	explicit vec4(const t_type val)					: x(val), y(val), z(val), w(val) {}
	vec4(const vec4& other)					: x(other.x), y(other.y), z(other.z), w(other.w) {}
	vec4(const t_type x, const t_type y, const t_type z, const t_type w) : x(x), y(y), z(z), w(w) {}
	vec4(const vec3<t_type>& other, const t_type w) : x(other.x), y(other.y), z(other.z), w(w) {}

	// assignment
	vec4& operator=(const vec4& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return (*this);
	}
	
	vec4& operator+=(const vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return (*this);
	}

	vec4& operator-=(const vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return (*this);
	}

	vec4& operator*=(const vec4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return (*this);
	}

	vec4& operator*=(const t_type scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return (*this);
	}

	vec4& operator/=(const vec4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return (*this);
	}

	vec4& operator/=(const t_type scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
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

// ----------------------------------------------------------------------------
// comparison
template <typename t_type>
inline const bool operator==(const vec4<t_type>& a, const vec4<t_type>& b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}

// component-wise arithmetic
template <typename t_type>
inline const vec4<t_type> operator+(const vec4<t_type>& a)
{
	return vec4<t_type>(a.x, a.y, a.z, a.w);
}

template <typename t_type>
inline const vec4<t_type> operator-(const vec4<t_type>& a)
{
	return vec4<t_type>(-a.x, -a.y, -a.z, -a.w);
}

template <typename t_type>
inline const vec4<t_type> operator+(const vec4<t_type>& a, const vec4<t_type>& b)
{
	return vec4<t_type>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

template <typename t_type>
inline const vec4<t_type> operator-(const vec4<t_type>& a, const vec4<t_type>& b)
{
	return vec4<t_type>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

template <typename t_type>
inline const vec4<t_type> operator*(const vec4<t_type>& a, const vec4<t_type>& b)
{
	return vec4<t_type>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

template <typename t_type>
inline const vec4<t_type> operator/(const vec4<t_type>& a, const vec4<t_type>& b)
{
	return vec4<t_type>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

// scalar arithmetic
template <typename t_type>
inline const vec4<t_type> operator*(const vec4<t_type>& a, const t_type scalar)
{
	return vec4<t_type>(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);
}

template <typename t_type>
inline const vec4<t_type> operator*(const t_type scalar, const vec4<t_type>& a)
{
	return vec4<t_type>(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);
}

template <typename t_type>
inline const vec4<t_type> operator/(const vec4<t_type>& a, const t_type scalar)
{
	return vec4<t_type>(a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar);
}

template <typename t_type>
inline const vec4<t_type> operator/(const t_type scalar, const vec4<t_type>& a)
{
	return vec4<t_type>(scalar / a.x, scalar / a.y, scalar / a.z, scalar / a.w);
}

// vector arithmetic
template <typename t_type>
inline const t_type dot(const vec4<t_type>& a, const vec4<t_type>& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

template <typename t_type>
inline const f32 length(const vec4<t_type>& a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

template <typename t_type>
inline const vec4<t_type> normalize(const vec4<t_type>& a)
{
	f32 len = length(a);
	return vec4<t_type>(a.x / len, a.y / len, a.z / len, a.w / len);
}

template <typename t_type>
inline const bool equal(const vec4<t_type>& a, const vec4<t_type>& b, const f32 epsilon)
{
	f32 disp = length(a - b);
	return (disp < epsilon);
}

template <typename t_type>
inline const f32 angle(const vec3<t_type>& a, const vec3<t_type>& b)
{
	vec3<t_type> na = normalize(a);
	vec3<t_type> nb = normalize(b);
	f32 cosTheta = dot(na, nb);
	return acosf(cosTheta);
}

// ----------------------------------------------------------------------------
// common abbreviations

using vec2f = vec2<f32>;
using vec2i = vec2<s32>;
using vec3f = vec3<f32>;
using vec3i = vec3<s32>;
using vec4f = vec4<f32>;
using vec4i = vec4<s32>;

// ----------------------------------------------------------------------------
};
