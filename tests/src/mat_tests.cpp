#include <catch.hpp>

#include <floral.h>

TEST_CASE("gpds - mat3x3 test", "mat3x3") {
	using namespace floral;

	mat3x3f cm1(1.0f);
	REQUIRE(cm1[0][0] == 1.0f);
	REQUIRE(cm1[1][1] == 1.0f);
	REQUIRE(cm1[2][2] == 1.0f);

	vec3f v1(1.0f, 2.0f, 3.0f);
	vec3f v2(2.0f, 3.0f, 4.0f);

	vec3f v3 = v1 * cm1;
	REQUIRE( (v3 == vec3f(1.0f, 2.0f, 3.0f)) );
	mat3x3f cm2(v1, v2, v3);
	mat3x3f cm4(
			{1.0f, 2.0f, 3.0f},
			{2.0f, 3.0f, 4.0f},
			{1.0f, 2.0f, 3.0f});
	REQUIRE( (cm4 == cm2) );
	mat3x3f cm3 = cm2 * cm1;
	REQUIRE( (cm3 == cm2) );
};

TEST_CASE("gpds - mat4x4 test", "mat4x4") {
	using namespace floral;

	mat4x4f cm1(1.0f);
	REQUIRE(cm1[0][0] == 1.0f);
	REQUIRE(cm1[1][1] == 1.0f);
	REQUIRE(cm1[2][2] == 1.0f);
	REQUIRE(cm1[3][3] == 1.0f);

	vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
	vec4f v2(2.0f, 3.0f, 4.0f, 5.0f);

	vec4f v3 = v1 * cm1;
	REQUIRE( (v3 == vec4f(1.0f, 2.0f, 3.0f, 4.0f)) );
	vec4f v4(v3);
	mat4x4f cm2(v1, v2, v3, v4);
	mat4x4f cm3 = cm2 * cm1;
	REQUIRE( (cm3 == cm2) );
};
