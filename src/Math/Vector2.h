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

#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2
{
public:
    float x, y;

    Vector2() {}
    Vector2(float x, float y) : x(x), y(y) {}
    Vector2(const Vector2 &v) = default;

    Vector2 &operator=(const Vector2 &v) = default;

    Vector2 operator-() const;
    Vector2 operator+(const Vector2 &v) const;
    Vector2 operator-(const Vector2 &v) const;
    Vector2 operator*(float t) const;
    Vector2 operator/(float t) const;
    Vector2 &operator+=(const Vector2 &v);
    Vector2 &operator-=(const Vector2 &v);
    Vector2 &operator*=(float t);
    Vector2 &operator/=(float t);

    float Dot(const Vector2 &v) const;
    float Length() const;
    void Normalize();
    Vector2 Normalized() const;
};

inline Vector2 operator*(float t, const Vector2 &v) { return v * t; }

#endif // __VECTOR2_H__
