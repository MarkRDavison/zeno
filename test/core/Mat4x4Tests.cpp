#include <catch2/catch.hpp>
#include <zeno/Core/Mat4x4.hpp>

TEST_CASE("Testing mat4x4 1", "[Mat4x4]") {
	ze::Mat4x4 mat(1.0f);

	REQUIRE(1.0f == mat[0]);
}