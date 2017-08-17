#include <catch.hpp>

#include <math.h>
#include <floral.h>

TEST_CASE("gpds - vec2 test", "vec2") {
	using namespace floral;
	vec2f cv1;
	vec2f cv2(1.23f);
	vec2f cv3(cv2);
	vec2f cv4(1.23f, 2.34f);

	REQUIRE(cv1.x == 0.0f);
	REQUIRE(cv1.y == 0.0f);
	REQUIRE(cv2.x == 1.23f);
	REQUIRE(cv2.y == 1.23f);
	REQUIRE(cv3.x == 1.23f);
	REQUIRE(cv3.y == 1.23f);
	REQUIRE(cv4.x == 1.23f);
	REQUIRE(cv4.y == 2.34f);

	REQUIRE((cv2 == cv3) == true);

	vec2f v1(1.0f, 2.0f);
	vec2f v2(3.0f, 4.0f);

	v1 += v2;
	REQUIRE( (v1 == vec2f(4.0f, 6.0f)) );
	vec2f v3;
	v3 = v1 + v2;
	REQUIRE( (v3 == vec2f(7.0f, 10.0f)) );

	vec2f v4;
	v4 -= v1;
	REQUIRE( (v4 == vec2f(-4.0f, -6.0f)) );
	v4 = v2 - v1;
	REQUIRE( (v4 == vec2f(-1.0f, -2.0f)) );

	vec2f v5;
	v5 = v1 * v2;
	REQUIRE( (v5 == vec2f(12.0f, 24.0f)) );
	v5 *= v1;
	REQUIRE( (v5 == vec2f(48.0f, 144.0f)) );

	vec2f v6;
	v6 = v5 / v1;
	REQUIRE( (v6 == vec2f(12.0f, 24.0f)) );
	v6 /= v2;
	REQUIRE( (v6 == vec2f(4.0f, 6.0f)) );

	vec2f v7;
	v7 = -v6;
	REQUIRE( (v7 == vec2f(-4.0f, -6.0f)) );

	vec2f nv1(1.0f, 2.0f);
	vec2f nv2(3.0f, 4.0f);

	REQUIRE( nv1.dot(nv2) == 11.0f );
	REQUIRE( nv2.length() == 5.0f );
	vec2f nv3 = nv2.normalize();
	REQUIRE( (nv3 == vec2f(3.0f / 5.0f, 4.0f / 5.0f)) );
}

TEST_CASE("gpds - vec3 test", "vec3") {
	using namespace floral;
	vec3f cv1;
	vec3f cv2(1.23f);
	vec3f cv3(cv2);
	vec3f cv4(1.23f, 2.34f, 3.45f);

	REQUIRE(cv1.x == 0.0f);
	REQUIRE(cv1.y == 0.0f);
	REQUIRE(cv1.z == 0.0f);
	REQUIRE(cv2.x == 1.23f);
	REQUIRE(cv2.y == 1.23f);
	REQUIRE(cv2.z == 1.23f);
	REQUIRE(cv3.x == 1.23f);
	REQUIRE(cv3.y == 1.23f);
	REQUIRE(cv3.z == 1.23f);
	REQUIRE(cv4.x == 1.23f);
	REQUIRE(cv4.y == 2.34f);
	REQUIRE(cv4.z == 3.45f);

	REQUIRE((cv2 == cv3) == true);

	vec3f v1(1.0f, 2.0f, 3.0f);
	vec3f v2(4.0f, 5.0f, 6.0f);

	v1 += v2;
	REQUIRE( (v1 == vec3f(5.0f, 7.0f, 9.0f)) );
	vec3f v3;
	v3 = v1 + v2;
	REQUIRE( (v3 == vec3f(9.0f, 12.0f, 15.0f)) );

	vec3f v4;
	v4 -= v1;
	REQUIRE( (v4 == vec3f(-5.0f, -7.0f, -9.0f)) );
	v4 = v2 - v1;
	REQUIRE( (v4 == vec3f(-1.0f, -2.0f, -3.0f)) );

	vec3f v5;
	v5 = v1 * v2;
	REQUIRE( (v5 == vec3f(20.0f, 35.0f, 54.0f)) );
	v5 *= v1;
	REQUIRE( (v5 == vec3f(100.0f, 245.0f, 486.0f)) );

	vec3f v6;
	v6 = v5 / v1;
	REQUIRE( (v6 == vec3f(20.0f, 35.0f, 54.0f)) );
	v6 /= v2;
	REQUIRE( (v6 == vec3f(5.0f, 7.0f, 9.0f)) );

	vec3f v7;
	v7 = -v6;
	REQUIRE( (v7 == vec3f(-5.0f, -7.0f, -9.0f)) );

	vec3f nv1(1.0f, 2.0f, 3.0f);
	vec3f nv2(4.0f, 5.0f, 6.0f);

	REQUIRE( nv1.dot(nv2) == 32.0f );
	REQUIRE( nv2.length() == sqrt(77.0f) );
	vec3f nv3 = nv2.normalize();
	REQUIRE( (nv3 == vec3f(4.0f / sqrt(77.0f), 5.0f / sqrt(77.0f), 6.0f / sqrt(77.0f))) );
}

TEST_CASE("gpds - vec4 test", "vec4") {
	using namespace floral;
	vec4f cv1;
	vec4f cv2(1.23f);
	vec4f cv3(cv2);
	vec4f cv4(1.23f, 2.34f, 3.45f, 4.56f);

	REQUIRE(cv1.x == 0.0f);
	REQUIRE(cv1.y == 0.0f);
	REQUIRE(cv1.z == 0.0f);
	REQUIRE(cv1.w == 0.0f);
	REQUIRE(cv2.x == 1.23f);
	REQUIRE(cv2.y == 1.23f);
	REQUIRE(cv2.z == 1.23f);
	REQUIRE(cv2.w == 1.23f);
	REQUIRE(cv3.x == 1.23f);
	REQUIRE(cv3.y == 1.23f);
	REQUIRE(cv3.z == 1.23f);
	REQUIRE(cv3.w == 1.23f);
	REQUIRE(cv4.x == 1.23f);
	REQUIRE(cv4.y == 2.34f);
	REQUIRE(cv4.z == 3.45f);
	REQUIRE(cv4.w == 4.56f);

	REQUIRE((cv2 == cv3) == true);

	vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
	vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);

	v1 += v2;
	REQUIRE( (v1 == vec4f(5.0f, 7.0f, 9.0f, 11.0f)) );
	vec4f v3;
	v3 = v1 + v2;
	REQUIRE( (v3 == vec4f(9.0f, 12.0f, 15.0f, 18.0f)) );

	vec4f v4;
	v4 -= v1;
	REQUIRE( (v4 == vec4f(-5.0f, -7.0f, -9.0f, -11.0f)) );
	v4 = v2 - v1;
	REQUIRE( (v4 == vec4f(-1.0f, -2.0f, -3.0f, -4.0f)) );

	vec4f v5;
	v5 = v1 * v2;
	REQUIRE( (v5 == vec4f(20.0f, 35.0f, 54.0f, 77.0f)) );
	v5 *= v1;
	REQUIRE( (v5 == vec4f(100.0f, 245.0f, 486.0f, 847.0f)) );

	vec4f v6;
	v6 = v5 / v1;
	REQUIRE( (v6 == vec4f(20.0f, 35.0f, 54.0f, 77.0f)) );
	v6 /= v2;
	REQUIRE( (v6 == vec4f(5.0f, 7.0f, 9.0f, 11.0f)) );

	vec4f v7;
	v7 = -v6;
	REQUIRE( (v7 == vec4f(-5.0f, -7.0f, -9.0f, -11.0f)) );

	vec4f nv1(1.0f, 2.0f, 3.0f, 4.0f);
	vec4f nv2(4.0f, 5.0f, 6.0f, 7.0f);

	REQUIRE( nv1.dot(nv2) == 60.0f );
	REQUIRE( nv2.length() == sqrt(126.0f) );
	vec4f nv3 = nv2.normalize();
	REQUIRE( (nv3 == vec4f(4.0f / sqrt(126.0f), 5.0f / sqrt(126.0f), 6.0f / sqrt(126.0f), 7.0f / sqrt(126.0f))) );
}
