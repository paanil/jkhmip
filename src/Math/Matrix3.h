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

#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include "Vector3.h"

/// 3x3 Matrix class.
///
class Matrix3
{
public:
    /// Member data in union.
    /// data helps doing operations to all elements.
    /// mat is for operations like transpose.
    /// mij (where i = row, j = column) are for operations
    /// that need to be done memory layout independently.
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

//        // Rows are contiguous in memory.
//        struct
//        {
//            float m11, m12, m13;
//            float m21, m22, m23;
//            float m31, m32, m33;
//        };

        // Columns are contiguous in memory.
        struct
        {
            float m11, m21, m31;
            float m12, m22, m32;
            float m13, m23, m33;
        };
    };

    /// Constructors.
    Matrix3() {}
    Matrix3(const Matrix3 &m) = default;

    /// Assign operator.
    Matrix3 &operator=(const Matrix3 &m) = default;

    /// Basic matrix arithmetic.
    Matrix3 operator+(const Matrix3 &m) const;
    Matrix3 operator-(const Matrix3 &m) const;
    Matrix3 operator*(float t) const;
    Matrix3 operator/(float t) const;
    Matrix3 &operator+=(const Matrix3 &m);
    Matrix3 &operator-=(const Matrix3 &m);
    Matrix3 &operator*=(float t);
    Matrix3 &operator/=(float t);

    /// Matrix * matrix multiplication.
    /// Uses mathematical conventions.
    /// Example: Combining matrices A and B so that
    /// matrix A is applied first, then B looks like this:
    ///     M = B*A
    Matrix3 operator*(const Matrix3 &m) const;
    /// Matrix * vector multiplication.
    /// Uses mathematical conventions.
    /// Example: Apply matrix M to vector v:
    ///     v' = M*v
    Vector3 operator*(const Vector3 &v) const;

    /// Returns determinant of the matrix.
    float Determinant() const;
    /// Returns transpose of the matrix.
    Matrix3 Transposed() const;

    /* Static functions */

    /// Creates a zero matrix.
    static Matrix3 Zero();
    /// Creates an identity matrix.
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

/// Multily with scalar on the left.
inline Matrix3 operator*(float t, const Matrix3 &m) { return m * t; }

#endif // __MATRIX3_H__
