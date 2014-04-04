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

#include "Vector2.h"
#include "Math.h"

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2 &v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(float t) const
{
    return Vector2(x * t, y * t);
}

Vector2 Vector2::operator/(float t) const
{
    return Vector2(x / t, y / t);
}

Vector2 &Vector2::operator+=(const Vector2 &v)
{
    x += v.x; y += v.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &v)
{
    x -= v.x; y -= v.y;
    return *this;
}

Vector2 &Vector2::operator*=(float t)
{
    x *= t; y *= t;
    return *this;
}
Vector2 &Vector2::operator/=(float t)
{
    x /= t; y /= t;
    return *this;
}

float Vector2::Dot(const Vector2 &v) const
{
    return x*v.x + y*v.y;
}

float Vector2::LengthSqr() const
{
    return x*x + y*y;
}

float Vector2::Length() const
{
    return Math::Sqrt(x*x + y*y);
}

void Vector2::Normalize()
{
    float invLen = 1.0f / Length();
    x *= invLen; y *= invLen;
}

Vector2 Vector2::Normalized() const
{
    float invLen = 1.0f / Length();
    return Vector2(x * invLen, y * invLen);
}

void Vector2::SafeNormalize()
{
    float lenSqr = LengthSqr();
    if (lenSqr > Math::EPSILON)
    {
        float invLen = 1.0f / Math::Sqrt(lenSqr);
        x *= invLen; y *= invLen;
    }
}

Vector2 Vector2::SafeNormalized() const
{
    float lenSqr = LengthSqr();
    if (lenSqr > Math::EPSILON)
    {
        float invLen = 1.0f / Math::Sqrt(lenSqr);
        return Vector2(x * invLen, y * invLen);
    }
    return Vector2(0.0f, 0.0f);
}
