#include <zeno/Graphics/Colour.hpp>

#include <algorithm>

namespace ze {

	const Colour Colour::Black(0.0f, 0.0f, 0.0f);
	const Colour Colour::White(1.0f, 1.0f, 1.0f);
	const Colour Colour::Red(1.0f, 0.0f, 0.0f);
	const Colour Colour::Green(0.0f, 1.0f, 0.0f);
	const Colour Colour::Blue(0.0f, 0.0f, 1.0f);
	const Colour Colour::Yellow(1.0f, 1.0f, 0.0f);
	const Colour Colour::Magenta(1.0f, 0.0f, 1.0f);
	const Colour Colour::Cyan(0.0f, 1.0f, 1.0f);
	const Colour Colour::Transparent(0.0f, 0.0f, 0.0f, 0.0f);


	Colour::Colour(void) :
		r(0.0f),
		g(0.0f),
		b(0.0f),
		a(1.0f) {
	}
	Colour::Colour(float _r, float _g, float _b, float _a /*= 1.0f*/) :
		r(_r),
		g(_g),
		b(_b),
		a(_a) {
	}


	bool operator ==(const Colour& _left, const Colour& _right) {
		return (_left.r == _right.r &&
			_left.g == _right.g &&
			_left.b == _right.b &&
			_left.a == _right.a);
	}
	bool operator != (const Colour& _left, const Colour& _right) {
		return !(_left == _right);
	}

	Colour operator +(const Colour& _left, const Colour& _right) {
		return Colour(std::min(_left.r + _right.r, 1.0f),
			std::min(_left.g + _right.g, 1.0f),
			std::min(_left.b + _right.b, 1.0f),
			_left.a);
	}
	Colour& operator +=(Colour& _left, const Colour& _right) {
		_left = _left + _right;

		return _left;
	}

	Colour operator -(const Colour& _left, const Colour& _right) {
		return Colour(std::max(_left.r - _right.r, 0.0f),
			std::max(_left.g - _right.g, 0.0f),
			std::max(_left.b - _right.b, 0.0f),
			_left.a);
	}
	Colour& operator -=(Colour& _left, const Colour& _right) {
		_left = _left - _right;

		return _left;
	}

	Colour operator *(const Colour& _left, float _right) {
		return Colour(_left.r * _right,
			_left.g * _right,
			_left.b * _right,
			_left.a);
	}
	Colour operator *(const Colour& _left, const Colour& _right) {
		return Colour(_left.r * _right.r,
			_left.g * _right.g,
			_left.b * _right.b,
			_left.a * _right.a);

	}
	Colour& operator *=(Colour& _left, float _val) {
		_left.r *= _val;
		_left.g *= _val;
		_left.b *= _val;

		return _left;
	}
	Colour& operator *=(Colour& _left, const Colour& _right) {
		_left = _left * _right;

		return _left;
	}


	std::ostream& operator <<(std::ostream& os, Colour const& _col) {
		os << "r: " << _col.r << ", g: " << _col.g << ", b: " << _col.b << ", a: " << _col.a;
		return os;
	}

}