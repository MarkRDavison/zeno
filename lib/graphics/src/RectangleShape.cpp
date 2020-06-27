#include <zeno/Graphics/RectangleShape.hpp>

namespace ze {

	RectangleShape::RectangleShape(const Vector2f& _size, const Vector2f& _position /*= Vector2f()*/) {
		setTranslation(_position);
		setSize(_size);
		updateInternalColours();
	}


	void RectangleShape::setSize(const Vector2f& _size) {
		m_Points.clear();

		m_Points.push_back(Vector2f(0.0f, 0.0f));
		m_Points.push_back(Vector2f(_size.x, 0.0f));
		m_Points.push_back(Vector2f(_size.x, _size.y));
		m_Points.push_back(Vector2f(0.0f, _size.y));

		updateInternalPositions();
	}

}