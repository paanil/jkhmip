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

class Vector3
{
public:
    float x, y, z;

    Vector3() {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3(const Vector3 &v) = default;

    Vector3 &operator=(const Vector3 &v) = default;

    Vector3 operator-() const;
    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-(const Vector3 &v) const;
    Vector3 operator*(float t) const;
    Vector3 operator/(float t) const;
    Vector3 &operator+=(const Vector3 &v);
    Vector3 &operator-=(const Vector3 &v);
    Vector3 &operator*=(float t);
    Vector3 &operator/=(float t);

    float Dot(const Vector3 &v) const;
    float Length() const;
    void Normalize();
    Vector3 Normalized() const;
    Vector3 Cross(const Vector3 &v) const;
};

inline Vector3 operator*(float t, const Vector3 &v) { return v * t; }

#endif // __VECTOR3_H__
