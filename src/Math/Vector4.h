
#ifndef __VECTOR4_H__
#define __VECTOR4_H__

class Vector4
{
public:
    float x, y, z, w;

    Vector4() {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4(const Vector4 &v) = default;

    Vector4 &operator=(const Vector4 &v) = default;

    Vector4 operator-() const;
    Vector4 operator+(const Vector4 &v) const;
    Vector4 operator-(const Vector4 &v) const;
    Vector4 operator*(float t) const;
    Vector4 operator/(float t) const;
    Vector4 &operator+=(const Vector4 &v);
    Vector4 &operator-=(const Vector4 &v);
    Vector4 &operator*=(float t);
    Vector4 &operator/=(float t);

    float Dot(const Vector4 &v) const;
};

inline Vector4 operator*(float t, const Vector4 &v) { return v * t; }

#endif // __VECTOR4_H__
