#ifndef INCLUDED_ZENO_CORE_VECTOR_2_HPP_
#define INCLUDED_ZENO_CORE_VECTOR_2_HPP_

#include <iostream>

namespace ze {

	template <typename T>
	class Vector2 {
	public:

		Vector2() : Vector2(0, 0) {}
		Vector2(T _x, T _y) : x(_x), y(_y) {}

		template <typename U>
		Vector2(const Vector2<U>& _other) :
			Vector2(static_cast<T>(_other.x), static_cast<T>(_other.y)) {
		}


		T x;
		T y;

		inline bool empty() const {
			return x == 0 && y == 0;
		}
	};

	template <typename T>
	inline Vector2<T> operator*(const Vector2<T>& _lhs, T _rhs) {
		return Vector2<T>{_lhs.x* _rhs, _lhs.y* _rhs};
	}

	template <typename T>
	inline Vector2<T>& operator*=(Vector2<T>& _lhs, T _rhs) {
		_lhs.x *= _rhs;
		_lhs.y *= _rhs;
		return _lhs;
	}

	template <typename T>
	inline Vector2<T> operator*(T _lhs, const Vector2<T>& _rhs) {
		return Vector2<T>{_lhs * _rhs.x, _lhs * _rhs.y};
	}

	template <typename T>
	inline Vector2<T> operator/(const Vector2<T>& _lhs, T _rhs) {
		return Vector2<T>{_lhs.x / _rhs, _lhs.y / _rhs};
	}

	template <typename T>
	inline Vector2<T>& operator/=(Vector2<T>& _lhs, T _rhs) {
		_lhs.x /= _rhs;
		_lhs.y /= _rhs;
		return _lhs;
	}

	template <typename T>
	inline Vector2<T> operator+(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return Vector2<T>{_lhs.x + _rhs.x, _lhs.y + _rhs.y};
	}

	template <typename T>
	inline Vector2<T>& operator+=(Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		_lhs.x += _rhs.x;
		_lhs.y += _rhs.y;
		return _lhs;
	}

	template <typename T>
	inline Vector2<T> operator-(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return Vector2<T>{_lhs.x - _rhs.x, _lhs.y - _rhs.y};
	}
	template <typename T>
	inline Vector2<T>& operator-=(Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		_lhs.x -= _rhs.x;
		_lhs.y -= _rhs.y;
		return _lhs;
	}

	template <typename T>
	inline Vector2<T> operator-(const Vector2<T>& _vec) {
		return Vector2<T>{-_vec.x, -_vec.y};
	}

	template <typename T>
	inline bool operator==(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return _lhs.x == _rhs.x && _lhs.y == _rhs.y;
	}

	template <typename T>
	inline bool operator!=(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return !(_lhs.x == _rhs.x && _lhs.y == _rhs.y);
	}

	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const ze::Vector2<T>& t) {
		os << "(" << t.x << ", " << t.y << ")";
		return os;
	}

	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned>;
}

#endif // INCLUDED_ZENO_CORE_VECTOR_2_HPP_