
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
