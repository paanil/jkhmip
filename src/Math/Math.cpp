
#include "Math.h"

#include <cmath>

namespace Math
{

    float Sin(float angleRad)
    { return ::sinf(angleRad); }

    float Cos(float angleRad)
    { return ::cosf(angleRad); }

    float Tan(float angleRad)
    { return ::tanf(angleRad); }

    float Sqrt(float x)
    { return ::sqrtf(x); }

} // Math
