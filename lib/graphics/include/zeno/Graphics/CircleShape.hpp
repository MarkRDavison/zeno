#ifndef INCLUDED_ZENO_GRAPHICS_CIRCLE_SHAPE_HPP
#define INCLUDED_ZENO_GRAPHICS_CIRCLE_SHAPE_HPP

#include <zeno/Graphics/Shape.hpp>

namespace ze {

	class CircleShape : public Shape {
	public:
		CircleShape(float _radius, unsigned _points = 30);

		void setRadius(float _radius);
		void setPoints(unsigned _points);

	private:
		void regeneratePoints(void);

	private:
		unsigned m_CirclePoints;

		float m_Radius;
	};

}

#endif //~ INCLUDED_ZENO_GRAPHICS_CIRCLE_SHAPE_HPP