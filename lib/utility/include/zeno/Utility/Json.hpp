#ifndef INCLUDED_ZENO_UTILITY_JSON_HPP_
#define INCLUDED_ZENO_UTILITY_JSON_HPP_

#include <zeno/Core/Signal.hpp>
#include <vector>
#include <string>

namespace ze {

	class JsonToken {
	public:
		enum class Type {
			None = 0,
			ObjectStart,
			ObjectEnd,
			ArrayStart,
			ArrayEnd,
			ValueSeperator,
			Comma,
			ValueString,
			ValueNumber,
			ValueInteger,
			ValueBoolean
		} type;

		std::string content;
	};

	class JsonNode {
	public:
		~JsonNode();
		enum class Type {
			None = 0,
			Object,
			Array,
			ValueString,
			ValueNumber,
			ValueInteger,
			ValueBoolean
		} type;
		std::string name;
		JsonNode* parent{ nullptr };
		std::vector<JsonNode*> children;
		std::string content;
		float number;
		int integer;
		bool boolean;

		template<size_t N>
		JsonNode& operator[](const char _name[N]) const {
			return [std::string(_name)];
		}
		JsonNode& operator[](const std::string& _name) const;
		JsonNode& operator[](std::size_t _index) const;
	};

	class JsonDocument {
	public:
		JsonDocument();
		JsonDocument(JsonDocument& _document);
		~JsonDocument();

		void readFromText(const std::string& _text);
		void parse(const std::string& _text);
		const std::string& getInputRepresentation() const;

		Signal<JsonToken> tokenFound;
		JsonNode* m_Root{ nullptr };

	private:
		std::string m_Text;
	};

	class Json {
		Json() = delete;
		~Json() = delete;
	public:
		static JsonDocument parseFromText(const std::string& _text);
		static void createTreeFromStreamingDocument(JsonDocument& _document);
	};
}


#endif // INCLUDED_ZENO_UTILITY_JSON_HPP_