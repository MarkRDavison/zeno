#include <zeno/Utility/StringExtensions.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

namespace ze {

	std::string StringExtensions::loadFileToString(const std::string& _path) {
		std::string result;
		std::ifstream input;
		input.open(_path);

		if (!input.good()) {
			std::cerr << "Failed to load file: " << _path << std::endl;
			return std::string();
		}

		input.seekg(0, std::ios::end);
		result.reserve(static_cast<unsigned int>(input.tellg()));
		input.seekg(0, std::ios::beg);

		result.assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());

		return result;
	}

	std::vector<std::string> StringExtensions::splitStringByDelimeter(const std::string& _parameter, const std::string& _delimeter) {
		std::vector<std::string> result;
		std::stringstream stringStream(_parameter);
		std::string line;
		while (std::getline(stringStream, line)) {
			std::size_t prev = 0, pos;
			while ((pos = line.find_first_of(_delimeter, prev)) != std::string::npos) {
				if (pos > prev) {
					result.push_back(line.substr(prev, pos - prev));
				}
				prev = pos + 1;
			}
			if (prev < line.length()) {
				result.push_back(line.substr(prev, std::string::npos));
			}
		}

		return result;
	}

	std::size_t StringExtensions::hash(const std::string& _string) {
		return std::hash<std::string>{}(_string);
	}

	std::vector<std::string> StringExtensions::splitStringByString(const std::string& _string, const std::string& _splitString) {
		std::vector<std::string> returnValue;
		std::string string(_string);
		std::size_t loc;

		while (std::string::npos != (loc = string.find(_splitString))) {
			std::string pre = string.substr(0, loc);

			string = string.substr(loc + 1, std::string::npos);

			if (pre.size() > 0) {
				returnValue.push_back(pre);
			}
		}

		if (!string.empty()) {
			returnValue.push_back(string);
		}

		return returnValue;
	}

	bool StringExtensions::startsWith(const std::string& _str, const std::string& _start) {
		return (_str.find(_start) == 0);
	}
	bool StringExtensions::endsWith(const std::string& _str, const std::string& _end) {
		return (_str.find(_end) == _str.size() - _end.size());
	}

	std::string StringExtensions::stripLeadingWhitespace(const std::string& _str) {
		std::string str(_str);

		const std::string whitespace(" \n\r\t");

		while (str.find_first_of(whitespace) == 0) {
			str = str.substr(1, std::string::npos);
		}

		return str;
	}

	void StringExtensions::replaceAll(std::string& _string, const std::string& _substring, const std::string& _replacement) {
		std::size_t pos = 0;
		while ((pos = _string.find(_substring, pos)) != std::string::npos) {
			_string.replace(pos, _substring.size(), _replacement);

			pos += _replacement.size();
		}
	}
}