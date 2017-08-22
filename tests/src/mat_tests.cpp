#include <catch.hpp>

#include <floral.h>

TEST_CASE("mat3", "mat3x3") {
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

	mat3x3f cm5 = cm4 * 2.0f;
	mat3x3f cm5r(
			{2.0f, 4.0f, 6.0f},
			{4.0f, 6.0f, 8.0f},
			{2.0f, 4.0f, 6.0f});
	REQUIRE( (cm5 == cm5r) );
	cm5 *= 0.5f;
	REQUIRE( (cm5 == cm4) );
	mat3x3f cm6 = cm4 / 0.5f;
	REQUIRE( (cm6 == cm5r) );
	cm6 = cm6 / 2.0f;
	REQUIRE( (cm6 == cm4) );

	////////////////////////////////////////////
	mat3x3f cm6r(
			{3.0f, 0.0f, 2.0f},
			{2.0f, 0.0f, -2.0f},
			{0.0f, 1.0f, 1.0f});
	REQUIRE( cm6r.get_determinant() == 10.0f );	
	mat3x3f cm6ri(
			{0.2f, 0.2f, 0.0f},
			{-0.2f, 0.3f, 1.0f},
			{0.2f, -0.3f, 0.0f});
	REQUIRE( (cm6r.get_inverse() == cm6ri) );
	mat3x3f cm6rt(
			{3.0f, 2.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{2.0f, -2.0f, 1.0f});
	REQUIRE( (cm6r.get_transpose() == cm6rt) );
};

TEST_CASE("mat4", "mat4x4") {
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
	
	////////////////////////////////////////////
	mat4x4f cm6r(
			{-4.0f, 0.0f, 0.0f, 0.0f},
			{-1.0f, 2.0f, 0.0f, 0.0f},
			{-4.0f, 4.0f, 4.0f, 0.0f},
			{-1.0f, -9.0f, -1.0f, 1.0f});
	REQUIRE( cm6r.get_determinant() == -32.0f );

	mat4x4f cm6ri(
			{-0.25f, 0.0f, 0.0f, 0.0f},
			{-0.125f, 0.5f, 0.0f, 0.0f},
			{-0.125f, -0.5f, 0.25f, 0.0f},
			{-1.5f, 4.0f, 0.25f, 1.0f});
	REQUIRE( (cm6r.get_inverse() == cm6ri) );

	mat4x4f cm6rt(
			{-4.0f, -1.0f, -4.0f, -1.0f},
			{0.0f, 2.0f, 4.0f, -9.0f},
			{0.0f, 0.0f, 4.0f, -1.0f},
			{0.0f, 0.0f, 0.0f, 1.0f});
	REQUIRE( (cm6r.get_transpose() == cm6rt) );
};
