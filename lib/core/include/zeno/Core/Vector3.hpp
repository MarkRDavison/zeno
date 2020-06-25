#ifndef INCLUDED_ZENO_CORE_VECTOR_3_HPP_
#define INCLUDED_ZENO_CORE_VECTOR_3_HPP_

#include <zeno/Core/Vector2.hpp>

namespace ze {

    template <typename T>
    class Vector3 {
    public:

        Vector3() : Vector3(0, 0, 0) {}
        Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

        template <typename U>
        Vector3(const Vector3<U>& _other) : Vector3(static_cast<T>(_other.x_, static_cast<T>(_other.y), static_cast<T>(_other.z))) {}

        Vector3(const Vector2<T>& _other, T _z) : Vector3(_other.x, _other.y, _z) {}

        T x;
        T y;
        T z;

        Vector3<T> operator-(const Vector3<T>& _rhs) const {
            return { x - _rhs.x, y - _rhs.y, z - _rhs.z };
        }
        Vector3<T> operator+(const Vector3<T>& _rhs) const {
            return { x + _rhs.x, y + _rhs.y, z + _rhs.z };
        }

        void operator/=(T _value) {
            x /= _value;
            y /= _value;
            z /= _value;
        }

    };

    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;
    using Vector3u = Vector3<unsigned>;
}

#endif // INCLUDED_ZENO_CORE_VECTOR_3_HPP_