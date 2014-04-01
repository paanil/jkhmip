
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
