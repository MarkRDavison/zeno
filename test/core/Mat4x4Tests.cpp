#include <catch2/catch.hpp>
#include <zeno/Core/Mat4x4.hpp>


TEST_CASE("Mat4x4 Test default constructor", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4();

	REQUIRE(mat[0] == 0.0f);
	REQUIRE(mat[1] == 0.0f);
	REQUIRE(mat[2] == 0.0f);
	REQUIRE(mat[3] == 0.0f);

	REQUIRE(mat[4] == 0.0f);
	REQUIRE(mat[5] == 0.0f);
	REQUIRE(mat[6] == 0.0f);
	REQUIRE(mat[7] == 0.0f);

	REQUIRE(mat[8] == 0.0f);
	REQUIRE(mat[9] == 0.0f);
	REQUIRE(mat[10] == 0.0f);
	REQUIRE(mat[11] == 0.0f);

	REQUIRE(mat[12] == 0.0f);
	REQUIRE(mat[13] == 0.0f);
	REQUIRE(mat[14] == 0.0f);
	REQUIRE(mat[15] == 0.0f);
}
TEST_CASE("Mat4x4 Test scalar constructor", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4(9.0f);

	REQUIRE(mat[0] == 9.0f);
	REQUIRE(mat[1] == 0.0f);
	REQUIRE(mat[2] == 0.0f);
	REQUIRE(mat[3] == 0.0f);

	REQUIRE(mat[4] == 0.0f);
	REQUIRE(mat[5] == 9.0f);
	REQUIRE(mat[6] == 0.0f);
	REQUIRE(mat[7] == 0.0f);

	REQUIRE(mat[8] == 0.0f);
	REQUIRE(mat[9] == 0.0f);
	REQUIRE(mat[10] == 9.0f);
	REQUIRE(mat[11] == 0.0f);

	REQUIRE(mat[12] == 0.0f);
	REQUIRE(mat[13] == 0.0f);
	REQUIRE(mat[14] == 0.0f);
	REQUIRE(mat[15] == 9.0f);
}
TEST_CASE("Mat4x4 Test vector constructor", "[Mat4x4]") {
	ze::Vector3<float> x(1.0f, 2.0f, 3.0f);
	ze::Vector3<float> y(4.0f, 5.0f, 6.0f);
	ze::Vector3<float> z(7.0f, 8.0f, 9.0f);

	ze::Mat4x4 mat = ze::Mat4x4(x, y, z);

	REQUIRE(mat[0] == x.x);
	REQUIRE(mat[1] == x.y);
	REQUIRE(mat[2] == x.z);
	REQUIRE(mat[3] == 0.0f);

	REQUIRE(mat[4] == y.x);
	REQUIRE(mat[5] == y.y);
	REQUIRE(mat[6] == y.z);
	REQUIRE(mat[7] == 0.0f);

	REQUIRE(mat[8] == z.x);
	REQUIRE(mat[9] == z.y);
	REQUIRE(mat[10] == z.z);
	REQUIRE(mat[11] == 0.0f);

	REQUIRE(mat[12] == 0.0f);
	REQUIRE(mat[13] == 0.0f);
	REQUIRE(mat[14] == 0.0f);
	REQUIRE(mat[15] == 1.0f);
}
TEST_CASE("Mat4x4 Test 16 value constructor", "[Mat4x4]") {
	float _0 = 5.0f;
	float _1 = 9.0f;
	float _2 = 7.0f;
	float _3 = 11.0f;
	float _4 = 3.0f;
	float _5 = 13.0f;
	float _6 = 14.0f;
	float _7 = 4.0f;
	float _8 = 15.0f;
	float _9 = 0.0f;
	float _10 = 10.0f;
	float _11 = 6.0f;
	float _12 = 12.0f;
	float _13 = 2.0f;
	float _14 = 1.0f;
	float _15 = 8.0f;

	ze::Mat4x4 mat = ze::Mat4x4(_0, _4, _8, _12,
		_1, _5, _9, _13,
		_2, _6, _10, _14,
		_3, _7, _11, _15);

	REQUIRE(mat[0] == _0);
	REQUIRE(mat[1] == _1);
	REQUIRE(mat[2] == _2);
	REQUIRE(mat[3] == _3);
	REQUIRE(mat[4] == _4);
	REQUIRE(mat[5] == _5);
	REQUIRE(mat[6] == _6);
	REQUIRE(mat[7] == _7);
	REQUIRE(mat[8] == _8);
	REQUIRE(mat[9] == _9);
	REQUIRE(mat[10] == _10);
	REQUIRE(mat[11] == _11);
	REQUIRE(mat[12] == _12);
	REQUIRE(mat[13] == _13);
	REQUIRE(mat[14] == _14);
	REQUIRE(mat[15] == _15);
}
TEST_CASE("Mat4x4 Test copy constructor", "[Mat4x4]") {
	ze::Mat4x4 mat1 = ze::Mat4x4(1.5f);

	ze::Mat4x4 mat2 = ze::Mat4x4();

	REQUIRE_FALSE(mat1 == mat2);

	mat2 = mat1;

	REQUIRE(mat1 == mat2);
}
TEST_CASE("Mat4x4 Test data pointer", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4(1.45f);

	const float* data = mat.pointer();

	REQUIRE(data[0] == 1.45f);
	REQUIRE(data[1] == 0.0f);
	REQUIRE(data[2] == 0.0f);
	REQUIRE(data[3] == 0.0f);

	REQUIRE(data[4] == 0.0f);
	REQUIRE(data[5] == 1.45f);
	REQUIRE(data[6] == 0.0f);
	REQUIRE(data[7] == 0.0f);

	REQUIRE(data[8] == 0.0f);
	REQUIRE(data[9] == 0.0f);
	REQUIRE(data[10] == 1.45f);
	REQUIRE(data[11] == 0.0f);

	REQUIRE(data[12] == 0.0f);
	REQUIRE(data[13] == 0.0f);
	REQUIRE(data[14] == 0.0f);
	REQUIRE(data[15] == 1.45f);
}
TEST_CASE("Mat4x4 Test transpose method", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4(1.45f);

	REQUIRE(mat.transpose() == ze::Mat4x4(1.45f));

	mat[8] = 60.0f;

	mat.transpose();

	REQUIRE(mat[2] == 60.0f);
}
TEST_CASE("Mat4x4 Test inverse method", "[Mat4x4]") {
	ze::Vector3<float> x = ze::Vector3<float>(1.0f, 2.0f, 3.0f);
	ze::Vector3<float> y = ze::Vector3<float>(8.0f, 2.0f, -5.0f);
	ze::Vector3<float> z = ze::Vector3<float>(1.0f, -2.0f, 3.0f);
	ze::Mat4x4 mat = ze::Mat4x4(x, y, z);

	ze::Mat4x4 mat2 = mat;

	mat.inverse();

	ze::Mat4x4 id = mat * mat2;

	for (unsigned int i = 0; i < 16; i += 1, "[Mat4x4]") {
		REQUIRE(fabsf(id[i] - ze::Mat4x4(1.0f)[i]) < 0.001f);
	}
}
TEST_CASE("Mat4x4 Test Orthographic2D method", "[Mat4x4]") {
	ze::Vector2f size = ze::Vector2f(1920.0f, 1080.0f);

	ze::Vector3f posTL = ze::Vector3f(0.0f, size.y, 0.0f);
	ze::Vector3f posTR = ze::Vector3f(size.x, size.y, 0.0f);
	ze::Vector3f posBL = ze::Vector3f(0.0f, 0.0f, 0.0f);
	ze::Vector3f posBR = ze::Vector3f(size.x, 0.0f, 0.0f);


	ze::Mat4x4 mat = ze::Mat4x4::Orthographic2D(0.0f, size.x, size.y, 0.0f);

	REQUIRE(ze::Vector3f(-1.0f, +1.0f, 0.0f) == (mat * posTL));
	REQUIRE(ze::Vector3f(+1.0f, +1.0f, 0.0f) == (mat * posTR));
	REQUIRE(ze::Vector3f(-1.0f, -1.0f, 0.0f) == (mat * posBL));
	REQUIRE(ze::Vector3f(+1.0f, -1.0f, 0.0f) == (mat * posBR));
}
TEST_CASE("Mat4x4 Test Orthographic3D method", "[Mat4x4]") {
	ze::Vector3f size = ze::Vector3f(1920.0f, 1080.0f, 100.0f);

	ze::Vector3f posTLF = ze::Vector3f(0.0f, size.y, size.z);
	ze::Vector3f posTRF = ze::Vector3f(size.x, size.y, size.z);
	ze::Vector3f posBRF = ze::Vector3f(size.x, 0.0f, size.z);
	ze::Vector3f posBLF = ze::Vector3f(0.0f, 0.0f, size.z);

	ze::Vector3f posTLB = ze::Vector3f(0.0f, size.y, size.z * 2.0f);
	ze::Vector3f posTRB = ze::Vector3f(size.x, size.y, size.z * 2.0f);
	ze::Vector3f posBRB = ze::Vector3f(size.x, 0.0f, size.z * 2.0f);
	ze::Vector3f posBLB = ze::Vector3f(0.0f, 0.0f, size.z * 2.0f);


	ze::Mat4x4 mat = ze::Mat4x4::Orthographic3D(0.0f, size.x, size.y, 0.0f, size.z, size.z * 2.0f);

	REQUIRE(ze::Vector3f(-1.0f, +1.0f, -1.0f) == (mat * posTLF));
	REQUIRE(ze::Vector3f(+1.0f, +1.0f, -1.0f) == (mat * posTRF));
	REQUIRE(ze::Vector3f(+1.0f, -1.0f, -1.0f) == (mat * posBRF));
	REQUIRE(ze::Vector3f(-1.0f, -1.0f, -1.0f) == (mat * posBLF));


	REQUIRE(ze::Vector3f(-1.0f, +1.0f, +1.0f) == (mat * posTLB));
	REQUIRE(ze::Vector3f(+1.0f, +1.0f, +1.0f) == (mat * posTRB));
	REQUIRE(ze::Vector3f(+1.0f, -1.0f, +1.0f) == (mat * posBRB));
	REQUIRE(ze::Vector3f(-1.0f, -1.0f, +1.0f) == (mat * posBLB));
}
TEST_CASE("Mat4x4 Test = operator", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4(1.45f);

	ze::Mat4x4 mat2;

	mat = mat2;

	REQUIRE(mat == mat2);
}
TEST_CASE("Mat4x4 Test == operator", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4(1.23f);

	ze::Mat4x4 mat2 = ze::Mat4x4(1.22f);

	REQUIRE_FALSE(mat == mat2);

	mat2 = mat;

	REQUIRE(mat == mat2);
}
TEST_CASE("Mat4x4 Test != operator", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4(1.23f);

	ze::Mat4x4 mat2 = ze::Mat4x4(1.22f);

	REQUIRE(mat != mat2);

	mat2 = mat;

	REQUIRE_FALSE(mat != mat2);
}
TEST_CASE("Test Mat4x4 * Vector4 operation", "[Mat4x4]") {
	ze::Vector4f vec = ze::Vector4f(1.0f, 2.0f, 3.0f, 0.0f);
	ze::Mat4x4 mat = ze::Mat4x4(1.0f);

	REQUIRE(vec == (mat * vec));

	mat[0] = 2.0f;
	mat[5] = 2.0f;
	mat[10] = 2.0f;

	REQUIRE((vec * 2.0f) == (mat * vec));
}
TEST_CASE("Test Mat4x4 * Vector3 operation", "[Mat4x4]") {
	ze::Mat4x4 mat = ze::Mat4x4(1.0f);
	ze::Vector3f vec = ze::Vector3f(10.0f, 20.0f, 30.0f);

	REQUIRE(vec == (mat * vec));

	mat[0] = 2.0f;
	mat[5] = 2.0f;
	mat[10] = 2.0f;

	REQUIRE((vec * 2.0f) == (mat * vec));

	mat = ze::Mat4x4(1.0f);

	mat[12] = -1.0f;		//~ Translate left by one unit

	REQUIRE((vec - ze::Vector3f(1.0f, 0.0f, 0.0f)) == (mat * vec));
}
TEST_CASE("Test Mat4x4 * Mat4x4 operation", "[Mat4x4]") {
	ze::Mat4x4 mat1 = ze::Mat4x4(1.0f);
	ze::Mat4x4 mat2 = ze::Mat4x4(1.0f);

	REQUIRE(ze::Mat4x4(1.0f) == (mat1 * mat2));

	mat2[3] = 6.3f;
	mat2[9] = 2.1f;

	REQUIRE(mat2 == (mat1 * mat2));
}
TEST_CASE("Test scale method", "[Mat4x4]") {

	ze::Vector3f scale = ze::Vector3f(0.5f, 0.5f, 1.0f);

	ze::Mat4x4 mat = ze::Mat4x4::createScale(scale);

	ze::Vector3f vec = ze::Vector3f(8.0f, 8.0f, 0.0f);

	REQUIRE((vec / 2.0f) == (mat * vec));
}