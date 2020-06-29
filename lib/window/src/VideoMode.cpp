#include <zeno/Window/VideoMode.hpp>

namespace ze {

	VideoMode::VideoMode(unsigned _width, unsigned _height, const std::string& _title) :
		width(_width),
		height(_height),
		title(_title) {
	}

	VideoMode::VideoMode(const Vector2u& _size, const std::string& _title) :
		VideoMode(_size.x, _size.y, _title) {
	}

	VideoMode::VideoMode() :
		VideoMode(0, 0, "") {

	}


}