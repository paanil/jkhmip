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

#ifndef __VECTOR4_H__
#define __VECTOR4_H__

class Vector3;

/// 4-Dimensional vector class.
///
class Vector4
{
public:
    /// Memer data.
    float x, y, z, w;

    /// Constructors.
    Vector4() {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4(const Vector4 &v) = default;

    /// Assign operator.
    Vector4 &operator=(const Vector4 &v) = default;

    /// Basic vector arithmetic.
    Vector4 operator-() const;
    Vector4 operator+(const Vector4 &v) const;
    Vector4 operator-(const Vector4 &v) const;
    Vector4 operator*(float t) const;
    Vector4 operator/(float t) const;
    Vector4 &operator+=(const Vector4 &v);
    Vector4 &operator-=(const Vector4 &v);
    Vector4 &operator*=(float t);
    Vector4 &operator/=(float t);

    /// Returns dot product.
    float Dot(const Vector4 &v) const;
    /// Dot product assuming v.w = 1.
    float Dot(const Vector3 &v) const;

    /// Scales this with InvLength(xyz).
    void Normalize();
};

/// Multiply with scalar on the left.
inline Vector4 operator*(float t, const Vector4 &v) { return v * t; }

#endif // __VECTOR4_H__
