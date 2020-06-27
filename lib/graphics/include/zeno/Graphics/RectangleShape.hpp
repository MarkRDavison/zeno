#ifndef INCLUDED_ZENO_GRAPHICS_RECTANGLE_SHAPE_HPP
#define INCLUDED_ZENO_GRAPHICS_RECTANGLE_SHAPE_HPP

#include <zeno/Graphics/Shape.hpp>

namespace ze {

	class RectangleShape : public Shape {
	public:
		RectangleShape(const Vector2f& _size, const Vector2f& _position = Vector2f());

		void setSize(const Vector2f& _size);
	};

}

#endif //~ INCLUDED_ZENO_GRAPHICS_RECTANGLE_SHAPE_HPP