#ifndef INCLUDED_ZENO_CORE_VECTOR_4_HPP_
#define INCLUDED_ZENO_CORE_VECTOR_4_HPP_

#include <zeno/Core/Vector3.hpp>

namespace ze {

    template <typename T>
    class Vector4 {
    public:

        Vector4() : Vector4(0, 0, 0, 1) {}
        Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

        template <typename U>
        Vector4(const Vector4<U>& _other) :
            Vector4(static_cast<T>(_other.x_, static_cast<T>(_other.y), static_cast<T>(_other.z), static_cast<T>(_other.w))) {
        }

        Vector4(const Vector3<T>& _other, T _w) :
            Vector4(_other.x, _other.y, _other.z, _w) {
        }

        Vector4(const Vector2<T>& _other, T _z, T _w) :
            Vector4(_other.x, _other.y, _z, _w) {
        }

        T x;
        T y;
        T z;
        T w;
    };

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int>;
    using Vector4u = Vector4<unsigned>;
}

#endif // INCLUDED_ZENO_CORE_VECTOR_4_HPP_