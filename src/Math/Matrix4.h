/*
================================================================================

Copyright (c) 2014 Ilari Paananen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

================================================================================
*/

#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "Vector3.h"
#include "Vector4.h"

class Matrix4
{
public:

    union
    {
        struct
        {
            float data[16];
        };

        struct
        {
            float mat[4][4];
        };

//        // Rows are contiguous in memory.
//        struct
//        {
//            float m11, m12, m13, m14;
//            float m21, m22, m23, m24;
//            float m31, m32, m33, m34;
//            float m41, m42, m43, m44;
//        };

        // Columns are contiguous in memory.
        struct
        {
            float m11, m21, m31, m41;
            float m12, m22, m32, m42;
            float m13, m23, m33, m43;
            float m14, m24, m34, m44;
        };
    };

    Matrix4() {}
    Matrix4(const Matrix4 &m) = default;

    Matrix4 &operator=(const Matrix4 &m) = default;

    Matrix4 operator+(const Matrix4 &m) const;
    Matrix4 operator-(const Matrix4 &m) const;
    Matrix4 operator*(float t) const;
    Matrix4 operator/(float t) const;
    Matrix4 &operator+=(const Matrix4 &m);
    Matrix4 &operator-=(const Matrix4 &m);
    Matrix4 &operator*=(float t);
    Matrix4 &operator/=(float t);

    Matrix4 operator*(const Matrix4 &m) const;
    Vector3 operator*(const Vector3 &v) const;
    Vector4 operator*(const Vector4 &v) const;

    //TODO: float Determinant() const;
    Matrix4 Transposed() const;

    // Returns inverse of Translation * Rotation -matrix.
    // For test purposes only.
    Matrix4 InverseTR() const;

    /* Static functions */

    static Matrix4 Zero();
    static Matrix4 Identity();

    /// Creates a uniform scale matrix.
    static Matrix4 Scale(float scale);
    /// Creates a scale matrix.
    static Matrix4 Scale(float x, float y, float z);
    static Matrix4 Scale(const Vector3 &scale);

    /// Creates a rotation matrix from axis angle.
    /// Axis is expected to be a unit vector and angle in degrees.
    static Matrix4 Rotation(float x, float y, float z, float angle);
    static Matrix4 Rotation(const Vector3 &axis, float angle);

    /// Creates a translation matrix.
    static Matrix4 Translation(float x, float y, float z);
    static Matrix4 Translation(const Vector3 &translation);

    // Projections

    static Matrix4 Ortho(float w, float h, float zNear, float zFar);
    static Matrix4 Perspective(float fov, float aspect, float zNear, float zFar);
};

inline Matrix4 operator*(float t, const Matrix4 &m) { return m * t; }

#endif // __MATRIX4_H__
