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

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Vector3.h"

/// Quaternion class.
///
class Quaternion
{
public:
    /// Member data.
    float x, y, z, w;

    /// Constructors.
    Quaternion() {}
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Quaternion(const Quaternion &q) = default;

    /// Assign operator.
    Quaternion &operator=(const Quaternion &q) = default;

    /// Quaternion * quaternion multiplication.
    Quaternion operator*(const Quaternion &q) const;
    /// Quaternion * vector multiplication.
    /// Vector is converted to quaternion with w = 0.
    Quaternion operator*(const Vector3 &v) const;

    /// Rotates vector, i.e. returns
    /// (q * p * q^-1).xyz where q = this, p = quat(v,0).
    Vector3 RotateVector(const Vector3 &v) const;

    /// Returns inverse quaternion.
    Quaternion Inverse() const;
    /// Returns the dot product of this and q.
    float Dot(const Quaternion &q) const;
    /// Returns length of quaternion.
    float Length() const;
    /// Normalizes this. Unsafe if length = 0.
    void Normalize();
    /// Normalizes this safely. Does nothing if length = 0.
    void SafeNormalize();

    /* Static functions */

    /// Returns identity quaternion.
    static Quaternion Identity();

    /// Creates rotation quaternion from axis and angle.
    /// Axis must be unit length and angle in degrees.
    static Quaternion Rotation(const Vector3 &axis, float angle);

    /// Creates rotation quaternion that rotates around
    /// axis denoted by the name. Angle must be in degrees.
    static Quaternion RotationX(float angle);
    static Quaternion RotationY(float angle);
    static Quaternion RotationZ(float angle);

    /// Creates rotation from euler angles yaw, pitch and roll.
    /// yaw = angles.y, pitch = angles.x, roll = angles.z.
    static Quaternion RotationYXZ(const Vector3 &angles);
};

///// Spherical linear interpolation.
//Quaternion Slerp(const Quaternion &p, const Quaternion &q, float t);

#endif // __QUATERNION_H__
