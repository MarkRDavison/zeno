#ifndef INCLUDED_ZENO_CORE_TRANSFORMABLE2D_HPP_
#define INCLUDED_ZENO_CORE_TRANSFORMABLE2D_HPP_

#include <zeno/Core/Mat4x4.hpp>

namespace ze {

	class Transformable2D {
	public:
		Transformable2D();
		virtual ~Transformable2D();

		void reset();

		void translate(const Vector2f& _translation);
		void setTranslation(const Vector2f& _translation);
		Vector2f getTranslation(void) const;

		void scale(const Vector2f& _scale);
		void setScale(const Vector2f& _scale);
		Vector2f getScale(void) const;

		void rotate(float _rotation);
		void setRotation(float _rotation);
		float getRotation(void) const;

		void setOrigin(const Vector2f& _origin);
		Vector2f getOrigin(void) const;

		const Mat4x4& getAccumulatedTransform();

	private:
		Vector2f m_Position;
		Vector2f m_Scale;
		Vector2f m_Origin;
		float m_Rotation;

		Mat4x4 m_AccumulatedTransform;
	};

}

#endif // INCLUDED_ZENO_CORE_TRANSFORMABLE2D_HPP_