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
            Vector4(static_cast<T>(_other.x), static_cast<T>(_other.y), static_cast<T>(_other.z), static_cast<T>(_other.w)) {
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

    template <typename T>
    inline Vector4<T> operator*(const Vector4<T>& _lhs, T _rhs) {
        return Vector4<T>{_lhs.x* _rhs, _lhs.y* _rhs, _lhs.z* _rhs, _lhs.w};
    }

    template <typename T>
    inline Vector4<T>& operator*=(Vector4<T>& _lhs, T _rhs) {
        _lhs.x *= _rhs;
        _lhs.y *= _rhs;
        _lhs.z *= _rhs;
        return _lhs;
    }

    template <typename T>
    inline Vector4<T> operator*(T _lhs, Vector4<T>& _rhs) {
        return Vector4<T>{_rhs.x* _lhs, _rhs.y* _lhs, _rhs.z* _lhs, _rhs.w};
    }

    template <typename T>
    inline Vector4<T> operator/(const Vector4<T>& _lhs, T _rhs) {
        return Vector4<T>{_lhs.x / _rhs, _lhs.y / _rhs, _lhs.z / _rhs, _lhs.w};
    }

    template <typename T>
    inline Vector4<T>& operator/=(Vector4<T>& _lhs, T _rhs) {
        _lhs.x /= _rhs;
        _lhs.y /= _rhs;
        _lhs.z /= _rhs;
        return _lhs;
    }

    template <typename T>
    inline Vector4<T> operator+(const Vector4<T>& _lhs, const Vector4<T>& _rhs) {
        return Vector4<T>{_lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z, 1};
    }

    template <typename T>
    inline Vector4<T>& operator+=(Vector4<T>& _lhs, const Vector4<T>& _rhs) {
        _lhs.x += _rhs.x;
        _lhs.y += _rhs.y;
        _lhs.z += _rhs.z;
        return _lhs;
    }

    template <typename T>
    inline Vector4<T> operator-(const Vector4<T>& _vec) {
        return Vector4<T>{-_vec.x, -_vec.y, -_vec.z, _vec.w};
    }

    template <typename T>
    inline Vector4<T> operator-(const Vector4<T>& _lhs, const Vector4<T>& _rhs) {
        return Vector4<T>{_lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z - _rhs.z, 1};
    }
    template <typename T>
    inline Vector4<T>& operator-=(Vector4<T>& _lhs, const Vector4<T>& _rhs) {
        _lhs.x -= _rhs.x;
        _lhs.y -= _rhs.y;
        _lhs.z -= _rhs.z;
        return _lhs;
    }

    template <typename T>
    inline bool operator!=(const Vector4<T>& _lhs, const Vector4<T>& _rhs) {
        return
            _lhs.x != _rhs.x ||
            _lhs.y != _rhs.y ||
            _lhs.z != _rhs.z ||
            _lhs.w != _rhs.w;
    }
    template <typename T>
    inline bool operator==(const Vector4<T>& _lhs, const Vector4<T>& _rhs) {
        return !(_lhs != _rhs);
    }

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int>;
    using Vector4u = Vector4<unsigned>;
}

#endif // INCLUDED_ZENO_CORE_VECTOR_4_HPP_