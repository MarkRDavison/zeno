#include <zeno/Graphics/CircleShape.hpp>

#include <cmath>

namespace ze {

	CircleShape::CircleShape(float _radius, unsigned _points /*= 30*/) :
		m_CirclePoints(_points) {
		setRadius(_radius);
		updateInternalColours();
	}

	void CircleShape::setRadius(float _radius) {
		m_Radius = _radius;

		regeneratePoints();
	}
	void CircleShape::setPoints(unsigned _points) {
		m_CirclePoints = _points;

		regeneratePoints();
	}

	void CircleShape::regeneratePoints(void) {
		m_Points.clear();

		for (float angle = 0.0f; angle < 360.0f; angle += 360.0f / static_cast<float>(m_CirclePoints)) {
			float radian = angle * 3.14156265f / 180.0f;

			float x = m_Radius * sinf(radian);
			float y = m_Radius * cosf(radian);

			m_Points.push_back(Vector2f(x, y));
		}

		updateInternalPositions();
		updateOutlinePositions();
	}

}