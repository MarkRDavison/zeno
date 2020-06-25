#include <cmath>

namespace ze {

	template <typename T>
	T length(const Vector2<T>& _vec) {
		return static_cast<T>(std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y));
	}

	template <typename T>
	T length(const Vector3<T>& _vec) {
		return static_cast<T>(std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z));
	}

	template <typename T>
	T length(const Vector4<T>& _vec) {
		return static_cast<T>(std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z));
	}

	template <typename T>
	T distance(const Vector2<T>& _vec1, const Vector2<T>& _vec2) {
		return length(_vec2 - _vec1);
	}

	template <typename T>
	T distance(const Vector3<T>& _vec1, const Vector3<T>& _vec2) {
		return length(_vec2 - _vec1);
	}


	template <typename T>
	T lengthSquared(const Vector2<T>& _vec) {
		return _vec.x * _vec.x + _vec.y * _vec.y;
	}

	template <typename T>
	T lengthSquared(const Vector3<T>& _vec) {
		return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;
	}

	template <typename T>
	T lengthSquared(const Vector4<T>& _vec) {
		return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;
	}


	template <typename T>
	Vector2<T>& normalise(Vector2<T>& _vec) {
		const T l = length(_vec);
		_vec.x /= l;
		_vec.y /= l;

		return _vec;
	}
	template <typename T>
	Vector2<T> normalise(const Vector2<T>& _vec) {
		const T l = length(_vec);

		return Vector2<T>(_vec.x / l, _vec.y / l);
	}

	template <typename T>
	Vector3<T>& normalise(Vector3<T>& _vec) {
		_vec /= length(_vec);

		return _vec;
	}

	template <typename T>
	Vector4<T>& normalise(Vector4<T>& _vec) {
		_vec /= length(_vec);

		return _vec;
	}


	template <typename T>
	Vector3<T> cross(const Vector3<T>& _left, const Vector3<T>& _right) {
		return Vector3<T>(_left.y * _right.z - _left.z * _right.y,
			_left.z * _right.x - _left.x * _right.z,
			_left.x * _right.y - _left.y * _right.x);
	}

	template <typename T>
	Vector4<T> cross(const Vector4<T>& _left, const Vector4<T>& _right) {
		return Vector4<T>(_left.y * _right.z - _left.z * _right.y,
			_left.z * _right.x - _left.x * _right.z,
			_left.x * _right.y - _left.y * _right.x,
			static_cast<T>(1));
	}


	template <typename T>
	T dot(const Vector2<T>& _left, const Vector2<T>& _right) {
		return _left.x * _right.x + _left.y * _right.y;
	}

	template <typename T>
	T dot(const Vector3<T>& _left, const Vector3<T>& _right) {
		return _left.x * _right.x + _left.y * _right.y + _left.z * _right.z;
	}

	inline float toAngle(const Vector2<float>& _vec) {
		const float Radians = std::atan2(_vec.y, _vec.x);
		return Radians * 180.0f / static_cast<float>(3.14159265f);
	}

	inline Vector2<float> toDirection(float _angle) {
		_angle = _angle * static_cast<float>(3.14159265f) / 180.0f;
		return Vector2<float>(cosf(_angle), sinf(_angle));
	}

}