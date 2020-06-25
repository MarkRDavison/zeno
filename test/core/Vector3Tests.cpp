#include <catch2/catch.hpp>
#include <zeno/Core/Vector3.hpp>

TEST_CASE("Vector3 Test default constructor", "[Vector3]") {
	ze::Vector3<float> vec = ze::Vector3<float>();

	REQUIRE(vec.x == 0.0f);
	REQUIRE(vec.y == 0.0f);
	REQUIRE(vec.z == 0.0f);
}
TEST_CASE("Vector3 Test non-default constructor", "[Vector3]") {
	float x = 1.0f;
	float y = 12.0f;
	float z = -12.8f;
	ze::Vector3<float> vec = ze::Vector3<float>(x, y, z);

	REQUIRE(vec.x == x);
	REQUIRE(vec.y == y);
	REQUIRE(vec.z == z);
}
TEST_CASE("Vector3 Test copy constructor from same type", "[Vector3]") {
	float x = 1.2f;
	float y = 12.2f;
	float z = -12.8f;
	ze::Vector3<float> vec = ze::Vector3<float>(x, y, z);
	ze::Vector3<float> cpy = ze::Vector3<float>(vec);

	REQUIRE(cpy == vec);
}
TEST_CASE("Vector3 Test copy constructor from different type", "[Vector3]") {
	int x = 12;
	int y = 453;
	int z = -18;
	ze::Vector3<int> vec = ze::Vector3<int>(x, y, z);
	ze::Vector3<float> cpy = ze::Vector3<float>(vec);

	REQUIRE(cpy == ze::Vector3<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
}
TEST_CASE("Vector3 Test -(negate) operator", "[Vector3]") {
	float x = 12.3f;
	float y = -123.7f;
	float z = 88.1f;

	ze::Vector3<float> vec = ze::Vector3<float>(x, y, z);
	vec = -vec;

	REQUIRE(vec == ze::Vector3<float>(-x, -y, -z));
}
TEST_CASE("Vector3 TEST - operator", "[Vector3]") {
	float x = 12.6f;
	float y = 82.1f;
	float z = -12.8f;

	ze::Vector3<float> res = ze::Vector3<float>(x, y, z) - ze::Vector3<float>(x, y, z);

	REQUIRE(res == ze::Vector3<float>());
}
TEST_CASE("Vector3 TEST + operator", "[Vector3]") {
	float x = 12.6f;
	float y = 82.1f;
	float z = -12.8f;

	ze::Vector3<float> res = ze::Vector3<float>(x, y, z) + ze::Vector3<float>(x, y, z);

	REQUIRE(res.x == x * 2.0f);
	REQUIRE(res.y == y * 2.0f);
	REQUIRE(res.z == z * 2.0f);
}
TEST_CASE("Vector3 TEST += operator", "[Vector3]") {
	float x = 12.6f;
	float y = 82.1f;
	float z = -12.8f;

	ze::Vector3<float> res = ze::Vector3<float>(x, y, z);
	res += ze::Vector3<float>(x, y, z);

	REQUIRE(res.x == x * 2.0f);
	REQUIRE(res.y == y * 2.0f);
	REQUIRE(res.z == z * 2.0f);
}
TEST_CASE("Vector3 Test -= operator", "[Vector3]") {
	float x = 12.6f;
	float y = 82.1f;
	float z = -8.1f;

	ze::Vector3<float> res = ze::Vector3<float>(x, y, z);

	res -= ze::Vector3<float>(x, y, z);

	REQUIRE(res == ze::Vector3<float>());
}
TEST_CASE("Vector3 Test + operator", "[Vector3]") {
	float x = 12.6f;
	float y = 82.1f;
	float z = -8.9f;

	ze::Vector3<float> res = ze::Vector3<float>(x, y, z) + ze::Vector3<float>(x, y, z);

	REQUIRE(res == ze::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
}
TEST_CASE("Vector3 Test += operator", "[Vector3]") {
	float x = 12.6f;
	float y = 82.1f;
	float z = -8.5f;

	ze::Vector3<float> res = ze::Vector3<float>(x, y, z);
	res += res;

	REQUIRE(res == ze::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
}
TEST_CASE("Vector3 Test / operator", "[Vector3]") {
	float x = 123.75f;
	float y = 12.5f;
	float z = -23.4f;
	float div = 7.4f;

	ze::Vector3<float> vec = ze::Vector3<float>(x, y, z);
	vec = vec / div;

	REQUIRE(vec == ze::Vector3<float>(x / div, y / div, z / div));
}
TEST_CASE("Vector3 Test /= operator", "[Vector3]") {
	float x = 123.75f;
	float y = 12.5f;
	float z = -8.9f;
	float div = 7.4f;

	ze::Vector3<float> vec = ze::Vector3<float>(x, y, z);
	vec /= div;

	REQUIRE(vec == ze::Vector3<float>(x / div, y / div, z / div));
}
TEST_CASE("Vector3 Test * operator", "[Vector3]") {
	float x = 123.52f;
	float y = 7645.4f;
	float z = -123.6f;
	float mul = 2.1f;

	ze::Vector3<float> vec = ze::Vector3<float>(x, y, z);
	vec = vec * mul;

	REQUIRE(vec == ze::Vector3<float>(x * mul, y * mul, z * mul));


	vec = ze::Vector3<float>(x, y, z);
	vec = mul * vec;

	REQUIRE(vec == ze::Vector3<float>(x * mul, y * mul, z * mul));
}
TEST_CASE("Vector3 Test *= operator", "[Vector3]") {
	float x = 123.52f;
	float y = 7645.4f;
	float z = -764.4f;
	float mul = 2.1f;

	ze::Vector3<float> vec = ze::Vector3<float>(x, y, z);
	vec *= mul;

	REQUIRE(vec == ze::Vector3<float>(x * mul, y * mul, z * mul));
}
TEST_CASE("Vector3 Test == operator", "[Vector3]") {
	ze::Vector3<float> vec1 = ze::Vector3<float>(123.4f, 11.0f, -12.0f);
	ze::Vector3<float> vec2 = ze::Vector3<float>(13.4f, 1121.0f, -64.4f);

	REQUIRE_FALSE(vec1 == vec2);

	vec2 = vec1;
	REQUIRE(vec1 == vec2);
}
TEST_CASE("Vector3 Test != operator", "[Vector3]") {
	ze::Vector3<float> vec1 = ze::Vector3<float>(123.4f, 11.0f, -12.0f);
	ze::Vector3<float> vec2 = ze::Vector3<float>(13.4f, 1121.0f, -64.4f);

	REQUIRE(vec1 != vec2);

	vec2 = vec1;
	REQUIRE_FALSE(vec1 != vec2);
}