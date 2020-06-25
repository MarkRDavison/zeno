#include <catch2/catch.hpp>
#include <zeno/Core/Vector2.hpp>

TEST_CASE("Vector2 Test default constructor", "[Vector2]") {
	ze::Vector2<float> vec = ze::Vector2<float>();

	REQUIRE(vec.x == 0.0f);
	REQUIRE(vec.y == 0.0f);
}
TEST_CASE("Vector2 Test non-default constructor", "[Vector2]") {
	float x = 1.0f;
	float y = 12.0f;
	ze::Vector2<float> vec = ze::Vector2<float>(x, y);

	REQUIRE(vec.x == x);
	REQUIRE(vec.y == y);
}
TEST_CASE("Vector2 Test copy constructor from same type", "[Vector2]") {
	float x = 1.2f;
	float y = 12.2f;
	ze::Vector2<float> vec = ze::Vector2<float>(x, y);
	ze::Vector2<float> cpy = ze::Vector2<float>(vec);

	REQUIRE(cpy == vec);
}
TEST_CASE("Vector2 Test copy constructor from different type", "[Vector2]") {
	int x = 12;
	int y = 453;
	ze::Vector2<int> vec = ze::Vector2<int>(x, y);
	ze::Vector2<float> cpy = ze::Vector2<float>(vec);

	REQUIRE(cpy.x == static_cast<float>(x));
	REQUIRE(cpy.y == static_cast<float>(y));
}
TEST_CASE("Vector2 Test -(negate) operator", "[Vector2]") {
	float x = 12.3f;
	float y = -123.7f;

	ze::Vector2<float> vec = ze::Vector2<float>(x, y);
	vec = -vec;

	REQUIRE(vec.x == -x);
	REQUIRE(vec.y == -y);
}
TEST_CASE("Vector2 TEST - operator", "[Vector2]") {
	float x = 12.6f;
	float y = 82.1f;

	ze::Vector2<float> res = ze::Vector2<float>(x, y) - ze::Vector2<float>(x, y);

	REQUIRE(res == ze::Vector2<float>(0.0f, 0.0f));
}
TEST_CASE("Vector2 Test -= operator", "[Vector2]") {
	float x = 12.6f;
	float y = 82.1f;

	ze::Vector2<float> res = ze::Vector2<float>(x, y);

	res -= ze::Vector2<float>(x, y);

	REQUIRE(res == ze::Vector2<float>(0.0f, 0.0f));
}
TEST_CASE("Vector2 Test + operator", "[Vector2]") {
	float x = 12.6f;
	float y = 82.1f;

	ze::Vector2<float> res = ze::Vector2<float>(x, y) + ze::Vector2<float>(x, y);

	REQUIRE(res == ze::Vector2<float>(2.0f * x, 2.0f * y));
}
TEST_CASE("Vector2 Test += operator", "[Vector2]") {
	float x = 12.6f;
	float y = 82.1f;

	ze::Vector2<float> res = ze::Vector2<float>(x, y);
	res += res;

	REQUIRE(res == ze::Vector2<float>(2.0f * x, 2.0f * y));
}
TEST_CASE("Vector2 Test / operator", "[Vector2]") {
	float x = 123.75f;
	float y = 12.5f;
	float div = 7.4f;

	ze::Vector2<float> vec = ze::Vector2<float>(x, y);
	vec = vec / div;

	REQUIRE(vec == ze::Vector2<float>(x / div, y / div));
}
TEST_CASE("Vector2 Test /= operator", "[Vector2]") {
	float x = 123.75f;
	float y = 12.5f;
	float div = 7.4f;

	ze::Vector2<float> vec = ze::Vector2<float>(x, y);
	vec /= div;

	REQUIRE(vec == ze::Vector2<float>(x / div, y / div));
}
TEST_CASE("Vector2 Test * operator", "[Vector2]") {
	float x = 123.52f;
	float y = 7645.4f;
	float mul = 2.1f;

	ze::Vector2<float> vec = ze::Vector2<float>(x, y);
	vec = vec * mul;

	REQUIRE(vec == ze::Vector2<float>(x * mul, y * mul));


	vec = ze::Vector2<float>(x, y);
	vec = mul * vec;

	REQUIRE(vec == ze::Vector2<float>(x * mul, y * mul));
}
TEST_CASE("Vector2 Test *= operator", "[Vector2]") {
	float x = 123.52f;
	float y = 7645.4f;
	float mul = 2.1f;

	ze::Vector2<float> vec = ze::Vector2<float>(x, y);
	vec *= mul;

	REQUIRE(vec == ze::Vector2<float>(x * mul, y * mul));
}
TEST_CASE("Vector2 Test == operator", "[Vector2]") {
	ze::Vector2<float> vec1 = ze::Vector2<float>(123.4f, 11.0f);
	ze::Vector2<float> vec2 = ze::Vector2<float>(13.4f, 1121.0f);

	REQUIRE_FALSE(vec1 == vec2);

	vec2 = vec1;
	REQUIRE(vec1 == vec2);
}
TEST_CASE("Vector2 Test != operator", "[Vector2]") {
	ze::Vector2<float> vec1 = ze::Vector2<float>(123.4f, 11.0f);
	ze::Vector2<float> vec2 = ze::Vector2<float>(13.4f, 1121.0f);

	REQUIRE(vec1 != vec2);

	vec2 = vec1;
	REQUIRE_FALSE(vec1 != vec2);
}