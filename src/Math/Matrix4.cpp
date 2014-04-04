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

#include "Matrix4.h"
#include "Math.h"

Matrix4 Matrix4::operator+(const Matrix4 &m) const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.data[i] = data[i] + m.data[i];
    }
    return result;
}

Matrix4 Matrix4::operator-(const Matrix4 &m) const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.data[i] = data[i] - m.data[i];
    }
    return result;
}

Matrix4 Matrix4::operator*(float t) const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.data[i] = data[i] * t;
    }
    return result;
}

Matrix4 Matrix4::operator/(float t) const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.data[i] = data[i] / t;
    }
    return result;
}

Matrix4 &Matrix4::operator+=(const Matrix4 &m)
{
    for (int i = 0; i < 16; i++)
    {
        data[i] += m.data[i];
    }
    return *this;
}

Matrix4 &Matrix4::operator-=(const Matrix4 &m)
{
    for (int i = 0; i < 16; i++)
    {
        data[i] -= m.data[i];
    }
    return *this;
}

Matrix4 &Matrix4::operator*=(float t)
{
    for (int i = 0; i < 16; i++)
    {
        data[i] *= t;
    }
    return *this;
}

Matrix4 &Matrix4::operator/=(float t)
{
    for (int i = 0; i < 16; i++)
    {
        data[i] /= t;
    }
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 &m) const
{
    Matrix4 result;
    result.m11 = m11 * m.m11 + m12 * m.m21 + m13 * m.m31 + m14 * m.m41;
    result.m12 = m11 * m.m12 + m12 * m.m22 + m13 * m.m32 + m14 * m.m42;
    result.m13 = m11 * m.m13 + m12 * m.m23 + m13 * m.m33 + m14 * m.m43;
    result.m14 = m11 * m.m14 + m12 * m.m24 + m13 * m.m34 + m14 * m.m44;
    result.m21 = m21 * m.m11 + m22 * m.m21 + m23 * m.m31 + m24 * m.m41;
    result.m22 = m21 * m.m12 + m22 * m.m22 + m23 * m.m32 + m24 * m.m42;
    result.m23 = m21 * m.m13 + m22 * m.m23 + m23 * m.m33 + m24 * m.m43;
    result.m24 = m21 * m.m14 + m22 * m.m24 + m23 * m.m34 + m24 * m.m44;
    result.m31 = m31 * m.m11 + m32 * m.m21 + m33 * m.m31 + m34 * m.m41;
    result.m32 = m31 * m.m12 + m32 * m.m22 + m33 * m.m32 + m34 * m.m42;
    result.m33 = m31 * m.m13 + m32 * m.m23 + m33 * m.m33 + m34 * m.m43;
    result.m34 = m31 * m.m14 + m32 * m.m24 + m33 * m.m34 + m34 * m.m44;
    result.m41 = m41 * m.m11 + m42 * m.m21 + m43 * m.m31 + m44 * m.m41;
    result.m42 = m41 * m.m12 + m42 * m.m22 + m43 * m.m32 + m44 * m.m42;
    result.m43 = m41 * m.m13 + m42 * m.m23 + m43 * m.m33 + m44 * m.m43;
    result.m44 = m41 * m.m14 + m42 * m.m24 + m43 * m.m34 + m44 * m.m44;
    return result;
}

Vector3 Matrix4::operator*(const Vector3 &v) const
{
    Vector3 result;
    result.x = m11 * v.x + m12 * v.y + m13 * v.z + m14;
    result.y = m21 * v.x + m22 * v.y + m23 * v.z + m24;
    result.z = m31 * v.x + m32 * v.y + m33 * v.z + m34;
    return result;
}

Vector4 Matrix4::operator*(const Vector4 &v) const
{
    Vector4 result;
    result.x = m11 * v.x + m12 * v.y + m13 * v.z + m14 * v.w;
    result.y = m21 * v.x + m22 * v.y + m23 * v.z + m24 * v.w;
    result.z = m31 * v.x + m32 * v.y + m33 * v.z + m34 * v.w;
    result.w = m41 * v.x + m42 * v.y + m43 * v.z + m44 * v.w;
    return result;
}

Matrix4 Matrix4::Transposed() const
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.mat[i][j] = mat[j][i];
        }
    }
    return result;
}

Matrix4 Matrix4::InverseTR() const
{
    Matrix4 result = Zero();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.mat[i][j] = mat[j][i];
        }
    }

    Vector3 invTrans = result * Vector3(-m14, -m24, -m34);

    result.m14 = invTrans.x;
    result.m24 = invTrans.y;
    result.m34 = invTrans.z;
    result.m44 = 1.0f;

    return result;
}

Matrix4 Matrix4::Zero()
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.data[i] = 0.0f;
    }
    return result;
}

Matrix4 Matrix4::Identity()
{
    return Scale(1.0f, 1.0f, 1.0f);
}

Matrix4 Matrix4::Scale(float scale)
{
    return Scale(scale, scale, scale);
}

Matrix4 Matrix4::Scale(float x, float y, float z)
{
    Matrix4 result = Zero();
    result.m11 = x;
    result.m22 = y;
    result.m33 = z;
    result.m44 = 1.0f;
    return result;
}

Matrix4 Matrix4::Scale(const Vector3 &scale)
{
    return Scale(scale.x, scale.y, scale.z);
}

Matrix4 Matrix4::Rotation(float x, float y, float z, float angle)
{
    angle *= Math::DEG_TO_RAD;

    float s = Math::Sin(angle);
    float c = Math::Cos(angle);
    float t = 1.0f - c;

    Matrix4 result = Zero();
    result.m11 = x*x*t + c;
    result.m12 = x*y*t - z*s;
    result.m13 = x*z*t + y*s;
    result.m21 = x*y*t + z*s;
    result.m22 = y*y*t + c;
    result.m23 = y*z*t - x*s;
    result.m31 = x*z*t - y*s;
    result.m32 = y*z*t + x*s;
    result.m33 = z*z*t + c;
    result.m44 = 1.0f;
    return result;
}

Matrix4 Matrix4::Rotation(const Vector3 &axis, float angle)
{
    return Rotation(axis.x, axis.y, axis.z, angle);
}

Matrix4 Matrix4::Translation(float x, float y, float z)
{
    Matrix4 result = Identity();
    result.m14 = x;
    result.m24 = y;
    result.m34 = z;
    return result;
}

Matrix4 Matrix4::Translation(const Vector3 &translation)
{
    return Translation(translation.x, translation.y, translation.z);
}

Matrix4 Matrix4::Ortho(float w, float h, float zNear, float zFar)
{
    Matrix4 result = Zero();
    result.m11 = 2.0f / w;
    result.m22 = 2.0f / h;
    result.m33 = 2.0f / (zFar - zNear);
    result.m34 = -(zFar + zNear)/(zFar - zNear);
    result.m44 = 1.0f;
    return result;
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float zNear, float zFar)
{
    float f = 1.0f / Math::Tan(fov * Math::DEG_TO_RAD / 2.0f);

    Matrix4 result = Zero();
    result.m11 = f / aspect;
    result.m22 = f;
    result.m33 = (-zNear - zFar) / (zNear - zFar);
    result.m34 = 2.0f * zFar * zNear / (zNear - zFar);
    result.m43 = 1.0f;
    return result;
}
