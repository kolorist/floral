#ifndef __FLORAL_VEC_H__
#define __FLORAL_VEC_H__

#include <math.h>

#include <stdaliases.h>

namespace floral {

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
		// comparision
		const bool operator==(const vec2& other) {
			return (x == other.x && y == other.y);
		}
		// arthimetic: add, sub
		vec2& operator+=(const vec2& other) {
			x += other.x;
			y += other.y;
			return (*this);
		}

		vec2 operator+(const vec2& other) const {
			return vec2(x + other.x, y + other.y);
		}

		vec2& operator-=(const vec2& other) {
			x -= other.x;
			y -= other.y;
			return (*this);
		}

		vec2 operator-(const vec2& other) const {
			return vec2(x - other.x, y - other.y);
		}
		// scaling: mul, div, invert
		vec2& operator*=(const vec2& other) {
			x *= other.x;
			y *= other.y;
			return (*this);
		}

		vec2 operator*(const vec2& other) const {
			return vec2(x * other.x, y * other.y);
		}

		vec2 operator/=(const vec2& other) {
			x /= other.x;
			y /= other.y;
			return (*this);
		}
		
		vec2 operator/(const vec2& other) const {
			return vec2(x / other.x, y / other.y);
		}

		vec2 operator-() const {
			return vec2(-x, -y);
		}
		// dot and cross(there is no cross product between 2 vec2)
		const DType dot(const vec2& other) {
			return (x * other.x + y * other.y);
		}
		// length
		const DType length() const {
			return sqrt(x * x + y * y);
		}
		// normalize
		vec2 normalize() const {
			DType len = this->length();
			return vec2(x / len, y / len);
		}
		//--------------------------------------
		DType 									x, y;
	};

	template <class DType>
	struct vec3 {
		vec3()
			: x(0), y(0), z(0)
		{}

		explicit vec3(const DType val)
			: x(val), y(val), z(val)
		{}
		
		vec3(const vec3& other)
			: x(other.x), y(other.y), z(other.z)
		{}

		vec3(const DType xVal, const DType yVal, const DType zVal)
			: x(xVal), y(yVal), z(zVal)
		{}
		// comparision
		const bool operator==(const vec3& other) {
			return (x == other.x && y == other.y && z == other.z);
		}
		// arthimetic: add, sub
		vec3& operator+=(const vec3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return (*this);
		}

		vec3 operator+(const vec3& other) const {
			return vec3(x + other.x, y + other.y, z + other.z);
		}

		vec3& operator-=(const vec3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return (*this);
		}

		vec3 operator-(const vec3& other) const {
			return vec3(x - other.x, y - other.y, z - other.z);
		}
		// scaling: mul, div, invert
		vec3& operator*=(const vec3& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return (*this);
		}

		vec3 operator*(const vec3& other) const {
			return vec3(x * other.x, y * other.y, z * other.z);
		}

		vec3 operator/=(const vec3& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return (*this);
		}
		
		vec3 operator/(const vec3& other) const {
			return vec3(x / other.x, y / other.y, z / other.z);
		}

		vec3 operator-() const {
			return vec3(-x, -y, -z);
		}
		// dot and cross
		const DType dot(const vec3& other) {
			return (x * other.x + y * other.y + z * other.z);
		}
		vec3 cross(const vec3& other) {
			// xyzzy
			return vec3(
					y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
		}
		
		static vec3 cross(const vec3& lhs, const vec3& rhs) {
			return vec3(
					lhs.y * rhs.z - lhs.z * rhs.y,
					lhs.z * rhs.x - lhs.x * rhs.z,
					lhs.x * rhs.y - lhs.y * rhs.x);
		}
		
		// length
		const DType length() const {
			return sqrt(x * x + y * y + z * z);
		}
		// normalize
		vec3 normalize() const {
			DType len = this->length();
			return vec3(x / len, y / len, z / len);
		}
		//--------------------------------------
		DType 									x, y, z;
	};

	template <class DType>
	struct vec4 {
		vec4()
			: x(0), y(0), z(0), w(0)
		{}

		explicit vec4(const DType val)
			: x(val), y(val), z(val), w(val)
		{}
		
		vec4(const vec4& other)
			: x(other.x), y(other.y), z(other.z), w(other.w)
		{}

		vec4(const DType xVal, const DType yVal, const DType zVal, const DType wVal)
			: x(xVal), y(yVal), z(zVal), w(wVal)
		{}
		// comparision
		const bool operator==(const vec4& other) {
			return (x == other.x && y == other.y && z == other.z && w == other.w);
		}
		// arthimetic: add, sub
		vec4& operator+=(const vec4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return (*this);
		}

		vec4 operator+(const vec4& other) const {
			return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		vec4& operator-=(const vec4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return (*this);
		}

		vec4 operator-(const vec4& other) const {
			return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
		}
		// scaling: mul, div, invert
		vec4& operator*=(const vec4& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return (*this);
		}

		vec4 operator*(const vec4& other) const {
			return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		vec4 operator/=(const vec4& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return (*this);
		}
		
		vec4 operator/(const vec4& other) const {
			return vec4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		vec4 operator-() const {
			return vec4(-x, -y, -z, -w);
		}
		// transformation
		// dot and cross
		const DType dot(const vec4& other) {
			return (x * other.x + y * other.y + z * other.z + w * other.w);
		}
		// length
		const DType length() const {
			return sqrt(x * x + y * y + z * z + w * w);
		}
		// normalize
		vec4 normalize() const {
			DType len = this->length();
			return vec4(x / len, y / len, z / len, w / len);
		}
		//--------------------------------------
		DType									x, y, z, w;
	};

	////////////////////////////////////////////
	using vec2f = vec2<f32>;
	using vec2i = vec2<s32>;
	using vec3f = vec3<f32>;
	using vec3i = vec3<s32>;
	using vec4f = vec4<f32>;
	using vec4i = vec4<s32>;
};

#endif // __FLORAL_VEC_H__
