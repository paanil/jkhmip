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

#include "Quaternion.h"
#include "Math.h"

Quaternion Quaternion::operator*(const Quaternion &q) const
{
    Quaternion result;
    result.x = w*q.x + x*q.w + y*q.z - z*q.y;
    result.y = w*q.y - x*q.z + y*q.w + z*q.x;
    result.z = w*q.z + x*q.y - y*q.x + z*q.w;
    result.w = w*q.w - x*q.x - y*q.y - z*q.z;
    return result;
}

Quaternion Quaternion::operator*(const Vector3 &v) const
{
    return *this * Quaternion(v.x, v.y, v.z, 0.0f);
}

Vector3 Quaternion::RotateVector(const Vector3 &v) const
{
    Quaternion result = *this * v * Inverse();
    return Vector3(result.x, result.y, result.z);
}

Quaternion Quaternion::Inverse() const
{
    return Quaternion(-x, -y, -z, w);
}

float Quaternion::Dot(const Quaternion &q) const
{
    return x*q.w + y*q.y + z*q.z;
}

float Quaternion::Length() const
{
    return Math::Sqrt(x*x + y*y + z*z + w*w);
}

void Quaternion::Normalize()
{
    float invLen = 1.0f / Length();
    x *= invLen; y *= invLen; z *= invLen; w *= invLen;
}

void Quaternion::SafeNormalize()
{
    float lenSqr = x*x + y*y + z*z + w*w;
    if (lenSqr > Math::EPSILON)
    {
        float invLen = 1.0f / Math::Sqrt(lenSqr);
        x *= invLen; y *= invLen; z *= invLen; w *= invLen;
    }
}

Quaternion Quaternion::Identity()
{
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::Rotation(const Vector3 &axis, float angle)
{
    angle = angle * Math::DEG_TO_RAD / 2.0f;

    float s = Math::Sin(angle);

    Quaternion result;
    result.x = axis.x * s;
    result.y = axis.y * s;
    result.z = axis.z * s;
    result.w = Math::Cos(angle);
    return result;
}

Quaternion Quaternion::RotationX(float angle)
{
    angle = angle *  Math::DEG_TO_RAD / 2.0f;

    Quaternion result;
    result.x = Math::Sin(angle);
    result.y = 0.0f;
    result.z = 0.0f;
    result.w = Math::Cos(angle);
    return result;
}

Quaternion Quaternion::RotationY(float angle)
{
    angle = angle *  Math::DEG_TO_RAD / 2.0f;

    Quaternion result;
    result.x = 0.0f;
    result.y = Math::Sin(angle);
    result.z = 0.0f;
    result.w = Math::Cos(angle);
    return result;
}

Quaternion Quaternion::RotationZ(float angle)
{
    angle = angle *  Math::DEG_TO_RAD / 2.0f;

    Quaternion result;
    result.x = 0.0f;
    result.y = 0.0f;
    result.z = Math::Sin(angle);
    result.w = Math::Cos(angle);
    return result;
}

Quaternion Quaternion::RotationYXZ(const Vector3 &angles)
{
    //TODO: do this more optimally
    return RotationY(angles.y)*RotationX(angles.x)*RotationZ(angles.z);
}

//Quaternion Slerp(const Quaternion &p, const Quaternion &q, float t)
//{
//    if (t <= 0.0f) return p;
//    if (t >= 1.0f) return q;
//}
