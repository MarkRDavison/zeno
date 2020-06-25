#ifndef INCLUDED_ZENO_CORE_MAT_4X4_HPP
#define INCLUDED_ZENO_CORE_MAT_4X4_HPP

#include <zeno/Core/Vector3.hpp>
#include <zeno/Core/Vector4.hpp>
#include <ostream>

namespace ze {

    class Mat4x4 {
    public:
        Mat4x4(void);
        explicit Mat4x4(float _val);

        Mat4x4(Vector3<float> _x, Vector3<float> _y, Vector3<float> _z);

        Mat4x4(
            float _1, float _5, float _9, float _13,
            float _2, float _6, float _10, float _14,
            float _3, float _7, float _11, float _15,
            float _4, float _8, float _12, float _16);

        Mat4x4(const Mat4x4& _mat);

        void operator=(const Mat4x4& _right);

        float& operator[](int _right);

        const float& operator[](int _right) const;

        const float* pointer(void) const;

        Mat4x4& transpose(void);

        Mat4x4& inverse(void);

        static Mat4x4 Orthographic2D(const float& _left, const float& _right, const float& _top, const float& _bottom);
        static Mat4x4 Orthographic3D(const float& _left, const float& _right, const float& _top, const float& _bottom, const float& _near, const float& _far);

        static Mat4x4 lookat(const Vector3<float>& _eye, const Vector3<float>& _pos, const Vector3<float>& _up);

        static Mat4x4 perspective(float _fov, float _aspectRatio, float _near, float _far);

        Mat4x4& translate(const Vector3f& _vec);

        static Mat4x4 createTranslation(const Vector3f& _vec);

        static Mat4x4 createRotationX(float _angle);
        static Mat4x4 createRotationY(float _angle);
        static Mat4x4 createRotationZ(float _angle);

        static Mat4x4 createScale(const Vector3f& _scale);

    private:
        float values[16];
    };

    std::ostream& operator<<(std::ostream& os, const Mat4x4& _mat);

    bool operator !=(const Mat4x4& _left, const Mat4x4& _right);
    bool operator ==(const Mat4x4& _left, const Mat4x4& _right);

    Vector4<float> operator*(const Mat4x4& _left, const Vector4<float>& _right);
    Vector3<float> operator*(const Mat4x4& _left, const Vector3<float>& _right);
    Vector2<float> operator*(const Mat4x4& _left, const Vector2<float>& _right);
    Mat4x4 operator*(const Mat4x4& _left, const Mat4x4& _right);
    Mat4x4 operator*=(Mat4x4& _left, const Mat4x4& _right);

}

#endif //~ INCLUDED_ZENO_CORE_MAT_4X4_HPP