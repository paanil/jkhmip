
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

Vector3 Vector3::Cross(const Vector3 &v) const
{
    return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
