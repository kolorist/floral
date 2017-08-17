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
};
