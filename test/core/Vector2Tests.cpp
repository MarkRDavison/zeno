#include <catch2/catch.hpp>
#include <zeno/Core/Vector2.hpp>

TEST_CASE("Testing vec2", "[Vector2]") {
	const float x = 1.0f;
	const float y = 562.0f;
	ze::Vector2f vec{x, y};

	REQUIRE(x == vec.x);
	REQUIRE(y == vec.y);
}