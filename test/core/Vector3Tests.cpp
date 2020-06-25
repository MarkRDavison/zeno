#include <catch2/catch.hpp>
#include <zeno/Core/Vector3.hpp>

TEST_CASE("Testing vec3", "[Vector3]") {
	const float x = 1.0f;
	const float y = 562.0f;
	const float z = -221.0f;
	ze::Vector3f vec{ x, y, z };

	REQUIRE(x == vec.x);
	REQUIRE(y == vec.y);
	REQUIRE(z == vec.z);
}