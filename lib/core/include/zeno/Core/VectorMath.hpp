#ifndef INCLUDED_ZENO_CORE_VECTOR_MATH_HPP
#define INCLUDED_ZENO_CORE_VECTOR_MATH_HPP

#include <zeno/Core/Vector4.hpp>

namespace ze {

    template <typename T>
    T distance(const Vector2<T>& _vec1, const Vector2<T>& _vec2);

    template <typename T>
    T distance(const Vector3<T>& _vec1, const Vector3<T>& _vec2);


    template <typename T>
    T length(const Vector2<T>& _vec);

    template <typename T>
    T length(const Vector3<T>& _vec);

    template <typename T>
    T length(const Vector4<T>& _vec);


    template <typename T>
    T lengthSquared(const Vector2<T>& _vec);

    template <typename T>
    T lengthSquared(const Vector3<T>& _vec);

    template <typename T>
    T lengthSquared(const Vector4<T>& _vec);


    template <typename T>
    Vector2<T>& normalise(Vector2<T>& _vec);
    template <typename T>
    Vector2<T> normalise(const Vector2<T>& _vec);

    template <typename T>
    Vector3<T>& normalise(Vector3<T>& _vec);

    template <typename T>
    Vector4<T>& normalise(Vector4<T>& _vec);


    template <typename T>
    Vector3<T> cross(const Vector3<T>& _left, const Vector3<T>& _right);

    template <typename T>
    Vector4<T> cross(const Vector4<T>& _left, const Vector4<T>& _right);


    template <typename T>
    T dot(const Vector2<T>& _left, const Vector2<T>& _right);

    template <typename T>
    T dot(const Vector3<T>& _left, const Vector3<T>& _right);

    float toAngle(const Vector2<float>& _vec);

    Vector2<float> toDirection(float _angle);

}

#include <zeno/Core/VectorMath.inl>

#endif //~ INCLUDED_ZENO_CORE_VECTOR_MATH_HPP