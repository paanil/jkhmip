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

#include "Math.h"

#include <cmath>

namespace Math
{

    float Sin(float angleRad)
    {
        return ::sinf(angleRad);
    }

    float Cos(float angleRad)
    {
        return ::cosf(angleRad);
    }

    float Tan(float angleRad)
    {
        return ::tanf(angleRad);
    }

    float Sqrt(float x)
    {
        return ::sqrtf(x);
    }

    float Min(float a, float b)
    {
        return a < b ? a : b;
    }

    float Max(float a, float b)
    {
        return a > b ? a : b;
    }

    float Clamp(float x, float minValue, float maxValue)
    {
        return (x < minValue) ? minValue : ((x > maxValue) ? maxValue : x);
    }

    float WrapAngleDegrees(float angle)
    {
        int n = angle / 360.0f;
        angle -= n * 360.0f;
        return (angle >= 360.0f) ? angle - 360.0f :
            ((angle < 0.0f) ? angle + 360.0f : angle);
    }

} // Math
