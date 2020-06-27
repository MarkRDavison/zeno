#include <catch2/catch.hpp>
#include <zeno/Utility.hpp>

TEST_CASE("splitStringByDelimeter", "[StringExtensions]") {
	const std::string text = "hello-delim-test-one-";
	const auto& split = ze::StringExtensions::splitStringByDelimeter(text, "-");

	REQUIRE(4 == split.size());
	REQUIRE("hello" == split[0]);
	REQUIRE("delim" == split[1]);
	REQUIRE("test" == split[2]);
	REQUIRE("one" == split[3]);
}

TEST_CASE("hash is constant", "[StringExtensions]") {
	const std::string t = "Hello";

	const auto h1 = ze::StringExtensions::hash(t);
	const auto h2 = ze::StringExtensions::hash(t);
	const auto h3 = ze::StringExtensions::hash("Hello");

	REQUIRE(h1 == h2);
	REQUIRE(h2 == h3);
	REQUIRE(h3 == ze::StringExtensions::hash(t));
}