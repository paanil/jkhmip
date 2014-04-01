
#include "Matrix3.h"
#include "Math.h"

Matrix3 Matrix3::operator+(const Matrix3 &m) const
{
    Matrix3 result;
    for (int i = 0; i < 9; i++)
    {
        result.data[i] = data[i] + m.data[i];
    }
    return result;
}

Matrix3 Matrix3::operator-(const Matrix3 &m) const
{
    Matrix3 result;
    for (int i = 0; i < 9; i++)
    {
        result.data[i] = data[i] - m.data[i];
    }
    return result;
}

Matrix3 Matrix3::operator*(float t) const
{
    Matrix3 result;
    for (int i = 0; i < 9; i++)
    {
        result.data[i] = data[i] * t;
    }
    return result;
}

Matrix3 Matrix3::operator/(float t) const
{
    Matrix3 result;
    for (int i = 0; i < 9; i++)
    {
        result.data[i] = data[i] / t;
    }
    return result;
}

Matrix3 &Matrix3::operator+=(const Matrix3 &m)
{
    for (int i = 0; i < 9; i++)
    {
        data[i] += m.data[i];
    }
    return *this;
}

Matrix3 &Matrix3::operator-=(const Matrix3 &m)
{
    for (int i = 0; i < 9; i++)
    {
        data[i] -= m.data[i];
    }
    return *this;
}

Matrix3 &Matrix3::operator*=(float t)
{
    for (int i = 0; i < 9; i++)
    {
        data[i] *= t;
    }
    return *this;
}

Matrix3 &Matrix3::operator/=(float t)
{
    for (int i = 0; i < 9; i++)
    {
        data[i] /= t;
    }
    return *this;
}

Matrix3 Matrix3::operator*(const Matrix3 &m) const
{
    Matrix3 result;
    result.m11 = m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
    result.m12 = m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
    result.m13 = m11 * m.m13 + m12 * m.m23 + m13 * m.m33;
    result.m21 = m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
    result.m22 = m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
    result.m23 = m21 * m.m13 + m22 * m.m23 + m23 * m.m33;
    result.m31 = m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
    result.m32 = m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
    result.m33 = m31 * m.m13 + m32 * m.m23 + m33 * m.m33;
    return result;
}

Vector3 Matrix3::operator*(const Vector3 &v) const
{
    Vector3 result;
    result.x = m11 * v.x + m12 * v.y + m13 * v.z;
    result.y = m21 * v.x + m22 * v.y + m23 * v.z;
    result.z = m31 * v.x + m32 * v.y + m33 * v.z;
    return result;
}

float Matrix3::Determinant() const
{
    return m11*(m22*m33 - m32*m23) - m12*(m21*m33 - m23*m31) + m13*(m21*m32 - m22*m31);
}

Matrix3 Matrix3::Transposed() const
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.mat[i][j] = mat[j][i];
        }
    }
    return result;
}

Matrix3 Matrix3::Zero()
{
    Matrix3 result;
    for (int i = 0; i < 9; i++)
    {
        result.data[i] = 0.0f;
    }
    return result;
}

Matrix3 Matrix3::Identity()
{
    return Scale(1.0f, 1.0f, 1.0f);
}

Matrix3 Matrix3::Scale(float scale)
{
    return Scale(scale, scale, scale);
}

Matrix3 Matrix3::Scale(float x, float y, float z)
{
    Matrix3 result = Zero();
    result.m11 = x;
    result.m22 = y;
    result.m33 = z;
    return result;
}

Matrix3 Matrix3::Scale(const Vector3 &scale)
{
    return Scale(scale.x, scale.y, scale.z);
}

Matrix3 Matrix3::Rotation(float x, float y, float z, float angle)
{
    float s = Math::Sin(angle);
    float c = Math::Cos(angle);
    float t = 1.0f - c;

    Matrix3 result;
    result.m11 = x*x*t + c;
    result.m12 = x*y*t - z*s;
    result.m13 = x*z*t + y*s;
    result.m21 = x*y*t + z*s;
    result.m22 = y*y*t + c;
    result.m23 = y*z*t - x*s;
    result.m31 = x*z*t - y*s;
    result.m32 = y*z*t + x*s;
    result.m33 = z*z*t + c;
    return result;
}

Matrix3 Matrix3::Rotation(const Vector3 &axis, float angle)
{
    return Rotation(axis.x, axis.y, axis.z, angle);
}
