
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
