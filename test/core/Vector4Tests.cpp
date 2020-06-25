#include <catch2/catch.hpp>
#include <zeno/Core/Vector4.hpp>

TEST_CASE("Testing vec4", "[Vector4]") {
	const float x = 1.0f;
	const float y = 562.0f;
	const float z = -221.0f;
	const float w = 1.0f;
	ze::Vector4f vec{ x, y, z, w };

	REQUIRE(x == vec.x);
	REQUIRE(y == vec.y);
	REQUIRE(z == vec.z);
	REQUIRE(w == vec.w);
}