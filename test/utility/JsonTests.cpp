#include <catch2/catch.hpp>
#include <zeno/Utility.hpp>

namespace ze {

    namespace Test {

        TEST_CASE("Sample json parsing works", "[Json]") {
            const std::string text = R"json(
{
    "menu": {
        "id": "file",
        "value" : "File",
        "popup" : {
            "menuitem": [
                { "value": "New", "onclick" : "CreateNewDoc()"},
                { "value": "Open", "onclick" : "OpenDoc()" },
                { "value": "Close", "onclick" : "CloseDoc()" },
                { "value": 55.5, "onclick" : "CloseDoc()" },
                { "value": 555, "onclick" : "CloseDoc()" },
                { "value": false, "onclick" : "CloseDoc()" },
                { "value": true, "onclick" : "CloseDoc()" }
            ]
        }
    }
})json";

            JsonDocument doc;

            std::vector<JsonToken> tokens;
            doc.tokenFound.registerCallback([&](JsonToken _token) -> void {
                tokens.push_back(_token);
                });

            doc.parse(text);

            REQUIRE(91 == tokens.size());
        }

        TEST_CASE("Default streaming method creates json tree as expected", "[Json]") {
            const std::string text = R"json(
{
    "menu": {
        "id": "file",
        "value" : "File",
        "popup" : {
            "menuitem": [
                { "value": "New", "onclick" : "CreateNewDoc()"},
                { "value": "Open", "onclick" : "OpenDoc()" },
                { "value": "Close", "onclick" : "CloseDoc()" },
                { "value": 55.5, "onclick" : "CloseDoc()" },
                { "value": 555, "onclick" : "CloseDoc()" },
                { "value": false, "onclick" : "CloseDoc()" },
                { "value": true, "onclick" : "CloseDoc()" }
            ]
        }
    }
})json";

            JsonDocument doc(Json::parseFromText(text));


        }

    }
}