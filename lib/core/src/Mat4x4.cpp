#include <zeno/Core/Mat4x4.hpp>
#include <zeno/Core/VectorMath.hpp>
#include <algorithm>
#include <sstream>

namespace ze {

    Mat4x4::Mat4x4(void) :
        Mat4x4(0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f)

    {
    }

    Mat4x4::Mat4x4(float _val) :
        Mat4x4(_val, 0.0f, 0.0f, 0.0f,
            0.0f, _val, 0.0f, 0.0f,
            0.0f, 0.0f, _val, 0.0f,
            0.0f, 0.0f, 0.0f, _val) {
    }

    Mat4x4::Mat4x4(Vector3<float> _x, Vector3<float> _y, Vector3<float> _z) :
        Mat4x4(_x.x, _y.x, _z.x, 0.0f,
            _x.y, _y.y, _z.y, 0.0f,
            _x.z, _y.z, _z.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f) {
    }
    //~ To change column/row major change this constructor

    Mat4x4::Mat4x4(float _1, float _5, float _9, float _13,
        float _2, float _6, float _10, float _14,
        float _3, float _7, float _11, float _15,
        float _4, float _8, float _12, float _16) {
        values[0] = _1;
        values[1] = _2;
        values[2] = _3;
        values[3] = _4;

        values[4] = _5;
        values[5] = _6;
        values[6] = _7;
        values[7] = _8;

        values[8] = _9;
        values[9] = _10;
        values[10] = _11;
        values[11] = _12;

        values[12] = _13;
        values[13] = _14;
        values[14] = _15;
        values[15] = _16;
    }

    Mat4x4::Mat4x4(const Mat4x4& _mat) {
        for (unsigned int i = 0; i < 16; i += 1) {
            values[i] = _mat.values[i];
        }
    }


    const float* Mat4x4::pointer(void) const {
        return &values[0];
    }

    Mat4x4& Mat4x4::transpose(void) {
        for (unsigned int i = 0; i < 4; i += 1) {
            for (unsigned int j = 0; j < 4; j += 1) {
                if (i <= j) continue;
                std::swap(values[i * 4 + j], values[j * 4 + i]);
            }
        }
        return *this;
    }

    Mat4x4& Mat4x4::inverse(void) {
        float inv[16];

        inv[0] = values[5] * values[10] * values[15] -
            values[5] * values[11] * values[14] -
            values[9] * values[6] * values[15] +
            values[9] * values[7] * values[14] +
            values[13] * values[6] * values[11] -
            values[13] * values[7] * values[10];

        inv[4] = -values[4] * values[10] * values[15] +
            values[4] * values[11] * values[14] +
            values[8] * values[6] * values[15] -
            values[8] * values[7] * values[14] -
            values[12] * values[6] * values[11] +
            values[12] * values[7] * values[10];

        inv[8] = values[4] * values[9] * values[15] -
            values[4] * values[11] * values[13] -
            values[8] * values[5] * values[15] +
            values[8] * values[7] * values[13] +
            values[12] * values[5] * values[11] -
            values[12] * values[7] * values[9];

        inv[12] = -values[4] * values[9] * values[14] +
            values[4] * values[10] * values[13] +
            values[8] * values[5] * values[14] -
            values[8] * values[6] * values[13] -
            values[12] * values[5] * values[10] +
            values[12] * values[6] * values[9];

        inv[1] = -values[1] * values[10] * values[15] +
            values[1] * values[11] * values[14] +
            values[9] * values[2] * values[15] -
            values[9] * values[3] * values[14] -
            values[13] * values[2] * values[11] +
            values[13] * values[3] * values[10];

        inv[5] = values[0] * values[10] * values[15] -
            values[0] * values[11] * values[14] -
            values[8] * values[2] * values[15] +
            values[8] * values[3] * values[14] +
            values[12] * values[2] * values[11] -
            values[12] * values[3] * values[10];

        inv[9] = -values[0] * values[9] * values[15] +
            values[0] * values[11] * values[13] +
            values[8] * values[1] * values[15] -
            values[8] * values[3] * values[13] -
            values[12] * values[1] * values[11] +
            values[12] * values[3] * values[9];

        inv[13] = values[0] * values[9] * values[14] -
            values[0] * values[10] * values[13] -
            values[8] * values[1] * values[14] +
            values[8] * values[2] * values[13] +
            values[12] * values[1] * values[10] -
            values[12] * values[2] * values[9];

        inv[2] = values[1] * values[6] * values[15] -
            values[1] * values[7] * values[14] -
            values[5] * values[2] * values[15] +
            values[5] * values[3] * values[14] +
            values[13] * values[2] * values[7] -
            values[13] * values[3] * values[6];

        inv[6] = -values[0] * values[6] * values[15] +
            values[0] * values[7] * values[14] +
            values[4] * values[2] * values[15] -
            values[4] * values[3] * values[14] -
            values[12] * values[2] * values[7] +
            values[12] * values[3] * values[6];

        inv[10] = values[0] * values[5] * values[15] -
            values[0] * values[7] * values[13] -
            values[4] * values[1] * values[15] +
            values[4] * values[3] * values[13] +
            values[12] * values[1] * values[7] -
            values[12] * values[3] * values[5];

        inv[14] = -values[0] * values[5] * values[14] +
            values[0] * values[6] * values[13] +
            values[4] * values[1] * values[14] -
            values[4] * values[2] * values[13] -
            values[12] * values[1] * values[6] +
            values[12] * values[2] * values[5];

        inv[3] = -values[1] * values[6] * values[11] +
            values[1] * values[7] * values[10] +
            values[5] * values[2] * values[11] -
            values[5] * values[3] * values[10] -
            values[9] * values[2] * values[7] +
            values[9] * values[3] * values[6];

        inv[7] = values[0] * values[6] * values[11] -
            values[0] * values[7] * values[10] -
            values[4] * values[2] * values[11] +
            values[4] * values[3] * values[10] +
            values[8] * values[2] * values[7] -
            values[8] * values[3] * values[6];

        inv[11] = -values[0] * values[5] * values[11] +
            values[0] * values[7] * values[9] +
            values[4] * values[1] * values[11] -
            values[4] * values[3] * values[9] -
            values[8] * values[1] * values[7] +
            values[8] * values[3] * values[5];

        inv[15] = values[0] * values[5] * values[10] -
            values[0] * values[6] * values[9] -
            values[4] * values[1] * values[10] +
            values[4] * values[2] * values[9] +
            values[8] * values[1] * values[6] -
            values[8] * values[2] * values[5];

        float det = values[0] * inv[0] + values[1] * inv[4] + values[2] * inv[8] + values[3] * inv[12];

        if (det == 0.0f) {
            return *this;
        }

        det = 1.0f / det;

        for (unsigned int i = 0; i < 16; i += 1) {
            values[i] = inv[i] * det;
        }

        return *this;
    }

    Mat4x4 Mat4x4::Orthographic2D(const float& _left, const float& _right, const float& _top, const float& _bottom) {
        Mat4x4 mat(1.0f);

        mat[0] = 2.0f / (_right - _left);
        mat[5] = 2.0f / (_top - _bottom);
        mat[10] = -1.0f;

        mat[12] = -(_right + _left) / (_right - _left);
        mat[13] = -(_top + _bottom) / (_top - _bottom);

        return mat;
    }

    Mat4x4 Mat4x4::Orthographic3D(const float& _left, const float& _right, const float& _top, const float& _bottom, const float& _near, const float& _far) {
        Mat4x4 mat(1.0f);

        mat[0] = 2.0f / (_right - _left);
        mat[5] = 2.0f / (_top - _bottom);
        mat[10] = 2.0f / (_far - _near);

        mat[12] = -(_right + _left) / (_right - _left);
        mat[13] = -(_top + _bottom) / (_top - _bottom);
        mat[14] = -(_far + _near) / (_far - _near);

        return mat;
    }

    Mat4x4 Mat4x4::lookat(const Vector3<float>& _eye, const Vector3<float>& _pos, const Vector3<float>& _up) {
        Vector3f forward = _pos - _eye;
        normalise(forward);

        Vector3f side = cross(forward, _up);
        normalise(side);

        Vector3f up = cross(side, forward);
        normalise(up);

        Mat4x4 mat;
        mat[0] = side.x;
        mat[4] = side.y;
        mat[8] = side.z;
        mat[12] = -dot(side, _eye);

        mat[1] = up.x;
        mat[5] = up.y;
        mat[9] = up.z;
        mat[13] = -dot(up, _eye);

        mat[2] = -forward.x;
        mat[6] = -forward.y;
        mat[10] = -forward.z;
        mat[14] = -dot(forward, _eye);

        mat[3] = 0.0f;
        mat[7] = 0.0f;
        mat[11] = 0.0f;
        mat[15] = 1.0f;

        return mat;
    }

    Mat4x4 Mat4x4::perspective(float _fov, float _aspectRatio, float _near, float _far) {
        Mat4x4 mat = Mat4x4(1.0f);

        const float ar = _aspectRatio;
        const float zNear = _near;
        const float zFar = _far;
        const float zRange = zNear - zFar;
        const float tanHalfFOV = tanf((_fov / 2.0f) * 3.14159265f / 180.0f);

        mat[0] = 1.0f / (tanHalfFOV * ar);
        mat[4] = 0.0f;
        mat[8] = 0.0f;
        mat[12] = 0.0f;

        mat[1] = 0.0f;
        mat[5] = 1.0f / tanHalfFOV;
        mat[9] = 0.0f;
        mat[13] = 0.0f;

        mat[2] = 0.0f;
        mat[6] = 0.0f;
        mat[10] = (-zNear - zFar) / zRange;
        mat[14] = 2.0f * zFar * zNear / zRange;

        mat[3] = 0.0f;
        mat[7] = 0.0f;
        mat[11] = 1.0f;
        mat[15] = 0.0f;

        return mat;
    }

    Mat4x4& Mat4x4::translate(const Vector3f& _vec) {
        values[12] += _vec.x;
        values[13] += _vec.y;
        values[14] += _vec.z;

        return *this;
    }
    Mat4x4  Mat4x4::createTranslation(const Vector3f& _vec) {
        return Mat4x4(1.0f).translate(_vec);
    }

    Mat4x4 Mat4x4::createRotationX(float _angle) {
        Mat4x4 mat(1.0f);

        mat[5] = +cosf(_angle);		mat[6] = -sinf(_angle);
        mat[9] = +sinf(_angle);		mat[10] = +cosf(_angle);

        return mat;
    }
    Mat4x4 Mat4x4::createRotationY(float _angle) {
        Mat4x4 mat(1.0f);

        mat[0] = +cosf(_angle);		mat[2] = +sinf(_angle);
        mat[8] = -sinf(_angle);		mat[10] = +cosf(_angle);

        return mat;
    }
    Mat4x4 Mat4x4::createRotationZ(float _angle) {
        Mat4x4 mat(1.0f);

        mat[0] = +cosf(_angle);		mat[1] = -sinf(_angle);
        mat[4] = +sinf(_angle);		mat[5] = +cosf(_angle);

        return mat;
    }
    Mat4x4 Mat4x4::createScale(const Vector3f& _scale) {
        return Mat4x4(_scale.x, 0.0f, 0.0f, 0.0f,
            0.0f, _scale.y, 0.0f, 0.0f,
            0.0f, 0.0f, _scale.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    std::ostream& operator<<(std::ostream& os, const Mat4x4& _mat) {
        os <<
            _mat[0] << " " << _mat[4] << " " << _mat[8] << " " << _mat[12] << std::endl <<
            _mat[1] << " " << _mat[5] << " " << _mat[9] << " " << _mat[13] << std::endl <<
            _mat[2] << " " << _mat[6] << " " << _mat[10] << " " << _mat[14] << std::endl <<
            _mat[3] << " " << _mat[7] << " " << _mat[11] << " " << _mat[15] << std::endl;

        return os;
    }

    bool operator ==(const Mat4x4& _left, const Mat4x4& _right) {
        return (_left[0] == _right[0] &&
            _left[1] == _right[1] &&
            _left[2] == _right[2] &&
            _left[3] == _right[3] &&

            _left[4] == _right[4] &&
            _left[5] == _right[5] &&
            _left[6] == _right[6] &&
            _left[7] == _right[7] &&

            _left[8] == _right[8] &&
            _left[9] == _right[9] &&
            _left[10] == _right[10] &&
            _left[11] == _right[11] &&

            _left[12] == _right[12] &&
            _left[13] == _right[13] &&
            _left[14] == _right[14] &&
            _left[15] == _right[15]);
    }

    bool operator !=(const Mat4x4& _left, const Mat4x4& _right) {
        return !(_left == _right);
    }

    Vector4<float> operator*(const Mat4x4& _left, const Vector4<float>& _right) {
        return Vector4<float>(_left[0] * _right.x + _left[4] * _right.y + _left[8] * _right.z + _left[12] * _right.w,
            _left[1] * _right.x + _left[5] * _right.y + _left[9] * _right.z + _left[13] * _right.w,
            _left[2] * _right.x + _left[6] * _right.y + _left[10] * _right.z + _left[14] * _right.w,
            _left[3] * _right.x + _left[7] * _right.y + _left[11] * _right.z + _left[15] * _right.w);
    }

    Vector3<float> operator*(const Mat4x4& _left, const Vector3<float>& _right) {
        Vector4<float> result = _left * Vector4<float>(_right, 1.0f);

        return Vector3<float>(result.x, result.y, result.z);
    }
    Vector2<float> operator*(const Mat4x4& _left, const Vector2<float>& _right) {
        Vector4<float> result = _left * Vector4<float>(_right.x, _right.y, 0.0f, 1.0f);

        return Vector2<float>(result.x, result.y);
    }

    Mat4x4 operator*(const Mat4x4& _left, const Mat4x4& _right) {
        Mat4x4 result;

        for (unsigned int i = 0; i < 4; i += 1) {
            for (unsigned int j = 0; j < 4; j += 1) {
                result[j * 4 + i] = _left[0 + i] * _right[0 + 4 * j] +
                    _left[4 + i] * _right[1 + 4 * j] +
                    _left[8 + i] * _right[2 + 4 * j] +
                    _left[12 + i] * _right[3 + 4 * j];
            }
        }

        return result;
    }
    Mat4x4 operator*=(Mat4x4& _left, const Mat4x4& _right) {
        _left = _left * _right;

        return _left;
    }

    float& Mat4x4::operator[](int _right) {
        return values[_right];
    }

    const float& Mat4x4::operator[](int _right) const {
        return values[_right];
    }

    void Mat4x4::operator=(const Mat4x4& _right) {
        for (unsigned int i = 0; i < 16; i += 1) {
            values[i] = _right.values[i];
        }
    }

}