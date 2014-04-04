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

#ifndef __VECTOR3_H__
#define __VECTOR3_H__

/// 3-Dimensional vector class.
///
class Vector3
{
public:
    /// Member data.
    float x, y, z;

    /// Constructors.
    Vector3() {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3(const Vector3 &v) = default;

    /// Assign operator.
    Vector3 &operator=(const Vector3 &v) = default;

    /// Basic vector arithmetic.
    Vector3 operator-() const;
    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-(const Vector3 &v) const;
    Vector3 operator*(float t) const;
    Vector3 operator/(float t) const;
    Vector3 &operator+=(const Vector3 &v);
    Vector3 &operator-=(const Vector3 &v);
    Vector3 &operator*=(float t);
    Vector3 &operator/=(float t);

    /// Returns dot product.
    float Dot(const Vector3 &v) const;
    /// Returns squared length of the vector.
    float LengthSqr() const;
    /// Returns length of the vector.
    float Length() const;
    /// Normalizes this vector.
    /// Not safe if length == 0.
    void Normalize();
    /// Returns normalized vector leaving this unchanged.
    /// Not safe if length == 0.
    Vector3 Normalized() const;
    /// Safe normalization.
    /// Leaves this unchanged if length == 0.
    void SafeNormalize();
    /// Returns 0-vector if length == 0.
    Vector3 SafeNormalized() const;
    /// Returns cross product.
    Vector3 Cross(const Vector3 &v) const;
};

/// Multily with scalar on the left.
inline Vector3 operator*(float t, const Vector3 &v) { return v * t; }

#endif // __VECTOR3_H__
