#include <catch2/catch.hpp>
#include <zeno/Graphics/Colour.hpp>

TEST_CASE("Colour Test default constructor", "[Colour]") {
	ze::Colour col = ze::Colour();

	REQUIRE((col.r == 0.0f &&
		col.g == 0.0f &&
		col.b == 0.0f &&
		col.a == 1.0f));
}
TEST_CASE("Colour Test non-default constructor", "[Colour]") {
	float r = 0.2f;
	float g = 0.4f;
	float b = 0.6f;
	float a = 0.8f;
	ze::Colour col = ze::Colour(r, g, b, a);

	REQUIRE((col.r == r &&
		col.g == g &&
		col.b == b &&
		col.a == a));
}
TEST_CASE("Colour Test Black ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Black;

	REQUIRE(col == ze::Colour(0.0f, 0.0f, 0.0f, 1.0f));
}
TEST_CASE("Colour Test White ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::White;

	REQUIRE(col == ze::Colour(1.0f, 1.0f, 1.0f));
}
TEST_CASE("Colour Test Red ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Red;

	REQUIRE(col == ze::Colour(1.0f, 0.0f, 0.0f));
}
TEST_CASE("Colour Test Green ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Green;

	REQUIRE(col == ze::Colour(0.0f, 1.0f, 0.0f));
}
TEST_CASE("Colour Test Blue ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Blue;

	REQUIRE(col == ze::Colour(0.0f, 0.0f, 1.0f));
}
TEST_CASE("Colour Test Yellow ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Yellow;

	REQUIRE(col == ze::Colour(1.0f, 1.0f, 0.0f));
}
TEST_CASE("Colour Test Magenta ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Magenta;

	REQUIRE(col == ze::Colour(1.0f, 0.0f, 1.0f));
}
TEST_CASE("Colour Test Cyan ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Cyan;

	REQUIRE(col == ze::Colour(0.0f, 1.0f, 1.0f));
}
TEST_CASE("Colour Test Transparent ze::Colour", "[Colour]") {
	ze::Colour col = ze::Colour::Transparent;

	REQUIRE(col == ze::Colour(0.0f, 0.0f, 0.0f, 0.0f));
}
TEST_CASE("Colour Test == operator", "[Colour]") {
	float r = 0.2f;
	float g = 0.4f;
	float b = 0.6f;
	float a = 0.8f;
	ze::Colour col = ze::Colour(r, g, b, a);

	REQUIRE(col == ze::Colour(r, g, b, a));

	REQUIRE_FALSE(col == ze::Colour(a, b, g, r));
}
TEST_CASE("Colour Test != operator", "[Colour]") {
	float r = 0.2f;
	float g = 0.4f;
	float b = 0.6f;
	float a = 0.8f;
	ze::Colour col = ze::Colour(r, g, b, a);

	REQUIRE_FALSE(col != ze::Colour(r, g, b, a));

	REQUIRE(col != ze::Colour(a, b, g, r));
}
TEST_CASE("Colour Test + operator", "[Colour]") {
	ze::Colour red = ze::Colour::Red;
	ze::Colour green = ze::Colour::Green;

	REQUIRE((red + green) == ze::Colour::Yellow);

	REQUIRE((red + red) == ze::Colour::Red);
}
TEST_CASE("Colour Test += operator", "[Colour]") {
	ze::Colour col = ze::Colour::Red;

	col += ze::Colour::Green;

	REQUIRE(col == ze::Colour::Yellow);
}
TEST_CASE("Colour Test - operator", "[Colour]") {
	ze::Colour yellow = ze::Colour::Yellow;
	ze::Colour red = ze::Colour::Red;

	REQUIRE((yellow - red) == ze::Colour::Green);

	REQUIRE((yellow - yellow) == ze::Colour::Black);
}
TEST_CASE("Colour Test -= operator", "[Colour]") {
	ze::Colour col = ze::Colour::Red;

	col -= ze::Colour::Red;

	REQUIRE(col == ze::Colour::Black);
}
TEST_CASE("Colour Test * operator (float)", "[Colour]") {
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;

	float val = 0.5f;

	ze::Colour col = ze::Colour(r, g, b);

	REQUIRE((col * val) == ze::Colour(r * val, g * val, b * val));
}
TEST_CASE("Colour Test * operator (Colour)", "[Colour]") {
	ze::Colour red = ze::Colour::Red;
	ze::Colour white = ze::Colour::White;

	REQUIRE((red * white) == ze::Colour::Red);
}
TEST_CASE("Colour Test *= operator (float)", "[Colour]") {
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;

	float val = 0.5f;

	ze::Colour col = ze::Colour(r, g, b);

	col *= val;

	REQUIRE(col == ze::Colour(r * val, g * val, b * val));
}
TEST_CASE("Colour Test *= operator (Colour)", "[Colour]") {
	ze::Colour red = ze::Colour::Red;
	ze::Colour white = ze::Colour::White;

	red *= white;

	REQUIRE(red == ze::Colour::Red);
}