#include <zeno/Core/Transformable2D.hpp>

namespace ze {

	Transformable2D::Transformable2D() :
		m_Scale(1.0f, 1.0f),
		m_Rotation(0.0f),
		m_AccumulatedTransform(1.0f) {

	}
	Transformable2D::~Transformable2D() {}

	void Transformable2D::reset() {
		m_AccumulatedTransform = Mat4x4(1.0f);
		m_Scale = { 1.0f, 1.0f };
		m_Position = { 0.0f, 0.0f };
		m_Rotation = 0.0f;
	}

	void Transformable2D::translate(const Vector2f& _translation) {
		m_AccumulatedTransform *= Mat4x4::createTranslation({ _translation, 0.0f });
		setTranslation({ _translation.x + m_Position.x , _translation.y + m_Position.y });
	}
	void Transformable2D::setTranslation(const Vector2f& _translation) {
		m_Position = _translation;
	}
	Vector2f Transformable2D::getTranslation(void) const {
		return m_Position;
	}

	void Transformable2D::scale(const Vector2f& _scale) {
		m_AccumulatedTransform *= Mat4x4::createScale({ _scale, 1.0f });
		setScale({ m_Scale.x * _scale.x, m_Scale.y * _scale.y });
	}
	void Transformable2D::setScale(const Vector2f& _scale) {
		m_Scale = _scale;
	}
	Vector2f Transformable2D::getScale(void) const {
		return m_Scale;
	}

	void Transformable2D::rotate(float _rotation) {
		m_AccumulatedTransform *= Mat4x4::createRotationZ(_rotation * 3.14159265f / 180.0f);
		setRotation(_rotation + m_Rotation);
	}
	void Transformable2D::setRotation(float _rotation) {
		m_Rotation = _rotation;
	}
	float Transformable2D::getRotation(void) const {
		return m_Rotation * 3.14159265f / 180.0f;
	}

	void Transformable2D::setOrigin(const Vector2f& _origin) {
		m_Origin = _origin;
	}
	Vector2f Transformable2D::getOrigin(void) const {
		return m_Origin;
	}

	const Mat4x4& Transformable2D::getAccumulatedTransform() {
		return m_AccumulatedTransform;
	}
}