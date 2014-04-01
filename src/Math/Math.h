
#ifndef __MATH_H__
#define __MATH_H__

namespace Math
{

    const float PI = 3.1415926535897932384626433832795;

    const float DEG_TO_RAD = PI / 180.0f;
    const float RAD_TO_DEG = 180.0f / PI;

    float Sin(float angleRad);
    float Cos(float angleRad);
    float Tan(float angleRad);

    float Sqrt(float x);

} // Math

#endif // __MATH_H__
