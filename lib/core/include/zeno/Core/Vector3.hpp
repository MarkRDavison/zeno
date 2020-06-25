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
        Vector3(const Vector3<U>& _other) : Vector3(static_cast<T>(_other.x), static_cast<T>(_other.y), static_cast<T>(_other.z)) {}

        Vector3(const Vector2<T>& _other, T _z) : Vector3(_other.x, _other.y, _z) {}

        T x;
        T y;
        T z;

        inline bool empty() const {
            return x == 0 && y == 0 && z == 0;
        }
    };
    
    template <typename T>
    inline Vector3<T> operator*(const Vector3<T>& _lhs, T _rhs) {
        return Vector3<T>{_lhs.x * _rhs, _lhs.y * _rhs, _lhs.z * _rhs};
    }

    template <typename T>
    inline Vector3<T>& operator*=(Vector3<T>& _lhs, T _rhs) {
        _lhs.x *= _rhs;
        _lhs.y *= _rhs;
        _lhs.z *= _rhs;
        return _lhs;
    }

    template <typename T>
    inline Vector3<T> operator*(T _lhs, Vector3<T>& _rhs) {
        return Vector3<T>{_rhs.x * _lhs, _rhs.y * _lhs, _rhs.z * _lhs};
    }
    
    template <typename T>
    inline Vector3<T> operator/(const Vector3<T>& _lhs, T _rhs) {
        return Vector3<T>{_lhs.x / _rhs, _lhs.y / _rhs, _lhs.z / _rhs};
    }

    template <typename T>
    inline Vector3<T>& operator/=(Vector3<T>& _lhs, T _rhs) {
        _lhs.x /= _rhs;
        _lhs.y /= _rhs;
        _lhs.z /= _rhs;
        return _lhs;
    }

    template <typename T>
    inline Vector3<T> operator+(const Vector3<T>& _lhs, const Vector3<T>& _rhs) {
        return Vector3<T>{_lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z};
    }

    template <typename T>
    inline Vector3<T>& operator+=(Vector3<T>& _lhs, const Vector3<T>& _rhs) {
        _lhs.x += _rhs.x;
        _lhs.y += _rhs.y;
        _lhs.z += _rhs.z;
        return _lhs;
    }

    template <typename T>
    inline Vector3<T> operator-(const Vector3<T>& _vec) {
        return Vector3<T>{-_vec.x, -_vec.y, -_vec.z};
    }

    template <typename T>
    inline Vector3<T> operator-(const Vector3<T>& _lhs, const Vector3<T>& _rhs) {
        return Vector3<T>{_lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z - _rhs.z};
    }
    template <typename T>
    inline Vector3<T>& operator-=(Vector3<T>& _lhs, const Vector3<T>& _rhs) {
        _lhs.x -= _rhs.x;
        _lhs.y -= _rhs.y;
        _lhs.z -= _rhs.z;
        return _lhs;
    }

    template <typename T>
    inline bool operator!=(const Vector3<T>& _lhs, const Vector3<T>& _rhs) {
        return
            _lhs.x != _rhs.x ||
            _lhs.y != _rhs.y ||
            _lhs.z != _rhs.z;
    }
    template <typename T>
    inline bool operator==(const Vector3<T>& _lhs, const Vector3<T>& _rhs) {
        return !(_lhs != _rhs);
    }


    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;
    using Vector3u = Vector3<unsigned>;
}

#endif // INCLUDED_ZENO_CORE_VECTOR_3_HPP_