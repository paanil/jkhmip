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

#include "Vector3.h"
#include "Math.h"

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(float t) const
{
    return Vector3(x * t, y * t, z * t);
}

Vector3 Vector3::operator/(float t) const
{
    return Vector3(x / t, y / t, z / t);
}

Vector3 &Vector3::operator+=(const Vector3 &v)
{
    x += v.x; y += v.y; z += v.z;
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &v)
{
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

Vector3 &Vector3::operator*=(float t)
{
    x *= t; y *= t; z *= t;
    return *this;
}

Vector3 &Vector3::operator/=(float t)
{
    x /= t; y /= t; z /= t;
    return *this;
}

float Vector3::Dot(const Vector3 &v) const
{
    return x*v.x + y*v.y + z*v.z;
}

float Vector3::LengthSqr() const
{
    return x*x + y*y + z*z;
}

float Vector3::Length() const
{
    return Math::Sqrt(x*x + y*y + z*z);
}

void Vector3::Normalize()
{
    float invLen = 1.0f / Length();
    x *= invLen; y *= invLen; z *= invLen;
}

Vector3 Vector3::Normalized() const
{
    float invLen = 1.0f / Length();
    return Vector3(x * invLen, y * invLen, z * invLen);
}

void Vector3::SafeNormalize()
{
    float lenSqr = LengthSqr();
    if (lenSqr > Math::EPSILON)
    {
        float invLen = 1.0f / Math::Sqrt(lenSqr);
        x *= invLen; y *= invLen; z *= invLen;
    }
}

Vector3 Vector3::SafeNormalized() const
{
    float lenSqr = LengthSqr();
    if (lenSqr > Math::EPSILON)
    {
        float invLen = 1.0f / Math::Sqrt(lenSqr);
        return Vector3(x * invLen, y * invLen, z * invLen);
    }
    return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Cross(const Vector3 &v) const
{
    return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
