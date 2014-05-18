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

#include "Vector4.h"
#include "Vector3.h"
#include "Math.h"

Vector4 Vector4::operator-() const
{
    return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+(const Vector4 &v) const
{
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4 &v) const
{
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 Vector4::operator*(float t) const
{
    return Vector4(x * t, y * t, z * t, w * t);
}

Vector4 Vector4::operator/(float t) const
{
    return Vector4(x / t, y / t, z / t, w / t);
}

Vector4 &Vector4::operator+=(const Vector4 &v)
{
    x += v.x; y += v.y; z += v.z; w += v.w;
    return *this;
}

Vector4 &Vector4::operator-=(const Vector4 &v)
{
    x -= v.x; y -= v.y; z -= v.z; w -= v.w;
    return *this;
}

Vector4 &Vector4::operator*=(float t)
{
    x *= t; y *= t; z *= t; w *= t;
    return *this;
}

Vector4 &Vector4::operator/=(float t)
{
    x /= t; y /= t; z /= t; w /= t;
    return *this;
}

float Vector4::Dot(const Vector4 &v) const
{
    return x*v.x + y*v.y + z*v.z + w*v.w;
}

float Vector4::Dot(const Vector3 &v) const
{
    return x*v.x + y*v.y + z*v.z + w;
}

void Vector4::Normalize()
{
    float invLen = 1.0f / Math::Sqrt(x*x + y*y + z*z);
    x *= invLen; y *= invLen; z *= invLen; w *= invLen;
}
