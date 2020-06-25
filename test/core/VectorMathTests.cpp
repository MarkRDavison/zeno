#include <catch2/catch.hpp>
#include <zeno/Core/VectorMath.hpp>

TEST_CASE("Testing VectorMath", "[VectorMath]") {
	ze::Vector2f v{ 1.0f, 1.0f };

	ze::normalise(v);

	REQUIRE(v.x != 1.0f);
	REQUIRE(v.y != 1.0f);
	REQUIRE(v.x == Approx(v.y));
}