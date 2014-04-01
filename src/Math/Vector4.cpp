
#include "Vector4.h"

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
