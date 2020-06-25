#ifndef INCLUDED_ZENO_GRAPHICS_COLOUR_HPP
#define INCLUDED_ZENO_GRAPHICS_COLOUR_HPP

#include <ostream>

namespace ze {

	class Colour {
	public:
		Colour(void);
		Colour(float _r, float _g, float _b, float _a = 1.0f);

		static const Colour Black;
		static const Colour White;
		static const Colour Red;
		static const Colour Green;
		static const Colour Blue;
		static const Colour Yellow;
		static const Colour Magenta;
		static const Colour Cyan;
		static const Colour Transparent;

	public:
		float r;
		float g;
		float b;
		float a;
	};


	bool operator ==(const Colour& _left, const Colour& _right);

	bool operator != (const Colour& _left, const Colour& _right);

	Colour operator +(const Colour& _left, const Colour& _right);

	Colour& operator +=(Colour& _left, const Colour& _right);

	Colour operator -(const Colour& _left, const Colour& _right);

	Colour& operator -=(Colour& _left, const Colour& _right);

	Colour operator *(const Colour& _left, float _right);

	Colour operator *(const Colour& _left, const Colour& _right);

	Colour& operator *=(Colour& _left, float _val);

	Colour& operator *=(Colour& _left, const Colour& _right);

	std::ostream& operator <<(std::ostream& os, Colour const& _col);

}

#endif //~ INCLUDED_ZENO_GRAPHICS_COLOUR_HPP