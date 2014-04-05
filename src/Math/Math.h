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

#ifndef __MATH_H__
#define __MATH_H__

/// Namespace for math operations and constants.
///
namespace Math
{

    const float PI = 3.1415926535897932384626433832795;

    const float DEG_TO_RAD = PI / 180.0f;
    const float RAD_TO_DEG = 180.0f / PI;

    const float EPSILON = 0.0000001f;

    float Sin(float angleRad);
    float Cos(float angleRad);
    float Tan(float angleRad);

    float Sqrt(float x);

    float Clamp(float x, float minValue, float maxValue);

    /// Wraps angle to range [0, 360).
    float WrapAngleDegrees(float angle);

} // Math

#endif // __MATH_H__
