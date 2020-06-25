#include <zeno/Window/VideoMode.hpp>

namespace ze {

	VideoMode::VideoMode(unsigned _width, unsigned _height, const std::string& _title, int _decoration) :
		width(_width),
		height(_height),
		title(_title),
		decoration(_decoration) {
	}
	VideoMode::VideoMode(unsigned _width, unsigned _height, const std::string& _title) :
		VideoMode(_width, _height, _title, 1) {
	}

	VideoMode::VideoMode(const Vector2u& _size, const std::string& _title) :
		VideoMode(_size.x, _size.y, _title) {
	}

	VideoMode::VideoMode() :
		VideoMode(0, 0, "") {

	}


}