
#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include "Vector3.h"

class Matrix3
{
public:

    union
    {
        struct
        {
            float data[9];
        };

        struct
        {
            float mat[3][3];
        };

        // Rows are contiguous in memory.
        struct
        {
            float m11, m12, m13;
            float m21, m22, m23;
            float m31, m32, m33;
        };

//        // Columns are contiguous in memory.
//        struct
//        {
//            float m11, m21, m31;
//            float m12, m22, m32;
//            float m13, m23, m33;
//        };
    };

    Matrix3() {}
    Matrix3(const Matrix3 &m) = default;

    Matrix3 &operator=(const Matrix3 &m) = default;

    Matrix3 operator+(const Matrix3 &m) const;
    Matrix3 operator-(const Matrix3 &m) const;
    Matrix3 operator*(float t) const;
    Matrix3 operator/(float t) const;
    Matrix3 &operator+=(const Matrix3 &m);
    Matrix3 &operator-=(const Matrix3 &m);
    Matrix3 &operator*=(float t);
    Matrix3 &operator/=(float t);

    Matrix3 operator*(const Matrix3 &m) const;
    Vector3 operator*(const Vector3 &v) const;

    float Determinant() const;
    Matrix3 Transposed() const;

    /* Static functions */

    static Matrix3 Zero();
    static Matrix3 Identity();

    /// Creates a uniform scale matrix.
    static Matrix3 Scale(float scale);
    /// Creates a scale matrix.
    static Matrix3 Scale(float x, float y, float z);
    static Matrix3 Scale(const Vector3 &scale);

    /// Creates a rotation matrix from axis angle.
    /// Axis is expected to be a unit vector and angle in degrees.
    static Matrix3 Rotation(float x, float y, float z, float angle);
    static Matrix3 Rotation(const Vector3 &axis, float angle);
};

inline Matrix3 operator*(float t, const Matrix3 &m) { return m * t; }

#endif // __MATRIX3_H__
