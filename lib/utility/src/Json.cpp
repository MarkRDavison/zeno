#include <zeno/Utility/Json.hpp>
#include <iostream>
#include <cassert>

#define TOKEN_START_OBJECT '{'
#define TOKEN_CLOSE_OBJECT '}'
#define TOKEN_START_ARRAY '['
#define TOKEN_CLOSE_ARRAY ']'
#define TOKEN_VALUE_SEP ':'
#define TOKEN_COMMA ','
#define TOKEN_QUOTE '"'
#define WHITESPACE " \t\n\r"
#define VALUE_AFTER_VALUE " \t\n\r,]}"
#define NUMBER_SEPERATOR '.'

namespace ze {

	JsonDocument::JsonDocument() {}
	JsonDocument::JsonDocument(JsonDocument& _document) {}
	JsonDocument::~JsonDocument() {}

	void JsonDocument::parse(const std::string& _text) {
		m_Text = _text;
		std::string text(_text);

		while (!text.empty()) {
			std::size_t nonWhitespaceIndex = text.find_first_not_of(WHITESPACE);
			if (nonWhitespaceIndex == std::string::npos) { break; }

			char c = text[nonWhitespaceIndex];
			JsonToken token;
			switch (c) {
			case TOKEN_START_OBJECT:
			{
				text.erase(0, nonWhitespaceIndex + 1);
				token.type = JsonToken::Type::ObjectStart;
				tokenFound.invoke(token);
				break;
			}
			case TOKEN_CLOSE_OBJECT:
			{
				text.erase(0, nonWhitespaceIndex + 1);
				token.type = JsonToken::Type::ObjectEnd;
				tokenFound.invoke(token);
				break;
			}
			case TOKEN_START_ARRAY:
			{
				text.erase(0, nonWhitespaceIndex + 1);
				token.type = JsonToken::Type::ArrayStart;
				tokenFound.invoke(token);
				break;
			}
			case TOKEN_CLOSE_ARRAY:
			{
				text.erase(0, nonWhitespaceIndex + 1);
				token.type = JsonToken::Type::ArrayEnd;
				tokenFound.invoke(token);
				break;
			}
			case TOKEN_QUOTE:
			{
				std::size_t quoteStart = nonWhitespaceIndex;
				std::size_t quoteEnd = text.find(TOKEN_QUOTE, quoteStart + 1);

				assert(quoteEnd != std::string::npos);
				assert(quoteStart < quoteEnd);

				token.type = JsonToken::Type::ValueString;
				token.content = text.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
				text.erase(0, quoteEnd + 1);
				tokenFound.invoke(token);

				break;
			}
			case TOKEN_VALUE_SEP:
			{
				text.erase(0, nonWhitespaceIndex + 1);
				token.type = JsonToken::Type::ValueSeperator;
				tokenFound.invoke(token);
				break;
			}
			case TOKEN_COMMA:
			{
				text.erase(0, nonWhitespaceIndex + 1);
				token.type = JsonToken::Type::Comma;
				tokenFound.invoke(token);
				break;
			}
			default:
			{
				std::size_t valueEnd = text.find_first_of(VALUE_AFTER_VALUE, nonWhitespaceIndex + 1);
				assert(valueEnd != std::string::npos);
				token.content = text.substr(nonWhitespaceIndex, valueEnd - nonWhitespaceIndex);
				if (token.content.find(NUMBER_SEPERATOR) != std::string::npos) {
					token.type = JsonToken::Type::ValueNumber;
				} else if (
					token.content == "true" ||
					token.content == "True" ||
					token.content == "TRUE" ||
					token.content == "false" ||
					token.content == "False" ||
					token.content == "FALSE") {
					token.type = JsonToken::Type::ValueBoolean;
				} else {
					token.type = JsonToken::Type::ValueInteger;
				}
				tokenFound.invoke(token);
				text.erase(0, valueEnd);
				break;
			}
			}
		}
	}
	const std::string& JsonDocument::getInputRepresentation() const {
		return m_Text;
	}

	JsonDocument Json::parseFromText(const std::string& _text) {
		JsonDocument doc;

		std::string json;
		std::vector<JsonToken> tokens;

		int callback = doc.tokenFound.registerCallback([&](JsonToken _token) -> void {
			switch (_token.type) {
			case JsonToken::Type::ObjectStart:
				json += "'{' ";
				break;
			case JsonToken::Type::ObjectEnd:
				json += "'}' ";
				break;
			case JsonToken::Type::ArrayStart:
				json += "'[' ";
				break;
			case JsonToken::Type::ArrayEnd:
				json += "']' ";
				break;
			case JsonToken::Type::ValueSeperator:
				json += "':' ";
				break;
			case JsonToken::Type::Comma:
				json += "',' ";
				break;
			case JsonToken::Type::ValueString:
				json += "'\"" + _token.content + "\"' ";
				break;
			case JsonToken::Type::ValueNumber:
			case JsonToken::Type::ValueInteger:
				json += "'" + _token.content + "' ";
				break;
			case JsonToken::Type::ValueBoolean:
				if (_token.content == "true" ||
					_token.content == "True" ||
					_token.content == "TRUE") {
					json += "'True' ";
				} else if (_token.content == "false" ||
					_token.content == "False" ||
					_token.content == "FALSE") {
					json += "'False' ";
				}
				break;
			default:
				assert(false);
			}
			tokens.push_back(_token);
			});

		doc.parse(_text);

		doc.tokenFound.unregisterCallback(callback);

		std::cout << json << std::endl;

		return doc;
	}
	void Json::createTreeFromStreamingDocument(JsonDocument& _document) {
		JsonNode* root{ nullptr };
		JsonNode* current{ root };

		int callbackId = _document.tokenFound.registerCallback([&](JsonToken _token) -> void {

			switch (_token.type) {
			case JsonToken::Type::ObjectStart:
			{
				break;
			}
			case JsonToken::Type::ObjectEnd:
			{
				break;
			}
			case JsonToken::Type::ArrayStart:
			{
				break;
			}
			case JsonToken::Type::ArrayEnd:
			{
				break;
			}
			case JsonToken::Type::ValueSeperator:
			{
				break;
			}
			case JsonToken::Type::Comma:
			{
				break;
			}
			case JsonToken::Type::ValueString:
			{
				break;
			}
			case JsonToken::Type::ValueNumber:
			{
				break;
			}
			case JsonToken::Type::ValueInteger:
			{
				break;
			}
			case JsonToken::Type::ValueBoolean:
			{
				break;
			}
			default:
				assert(false);
			}
			});

		_document.parse(_document.getInputRepresentation());

		_document.tokenFound.unregisterCallback(callbackId);

		_document.m_Root = root;
	}

}