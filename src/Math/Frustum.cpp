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

#include "Frustum.h"
#include "Matrix4.h"
#include "AABB.h"
#include "Math.h"

bool Frustum::TestAABB(const AABB &aabb) const
{
    for (int i = 0; i < 6; i++)
    {
        if (Math::Max(aabb.min.x * planes[i].x, aabb.max.x * planes[i].x) +
            Math::Max(aabb.min.y * planes[i].y, aabb.max.y * planes[i].y) +
            Math::Max(aabb.min.z * planes[i].z, aabb.max.z * planes[i].z) < -planes[i].w)
            return false;
    }
    return true;
}

bool Frustum::TestSphere(const Vector4 &sphere) const
{
    float dist;
    Vector4 center(sphere.x, sphere.y, sphere.z, 1.0);
    for (int i = 0; i < 6; i++)
    {
        dist = planes[i].Dot(center);
        if (dist < sphere.w) break;
    }
    return (dist > -sphere.w);
}

Frustum Frustum::Extract(const Matrix4 &viewProj)
{
    Frustum frus;

    // LEFT
    frus.planes[0].x = viewProj.m41 + viewProj.m11;
    frus.planes[0].y = viewProj.m42 + viewProj.m12;
    frus.planes[0].z = viewProj.m43 + viewProj.m13;
    frus.planes[0].w = viewProj.m44 + viewProj.m14;
    frus.planes[0].Normalize();

    // RIGHT
    frus.planes[1].x = viewProj.m41 - viewProj.m11;
    frus.planes[1].y = viewProj.m42 - viewProj.m12;
    frus.planes[1].z = viewProj.m43 - viewProj.m13;
    frus.planes[1].w = viewProj.m44 - viewProj.m14;
    frus.planes[1].Normalize();

    // BOTTOM
    frus.planes[2].x = viewProj.m41 + viewProj.m21;
    frus.planes[2].y = viewProj.m42 + viewProj.m22;
    frus.planes[2].z = viewProj.m43 + viewProj.m23;
    frus.planes[2].w = viewProj.m44 + viewProj.m24;
    frus.planes[2].Normalize();

    // TOP
    frus.planes[3].x = viewProj.m41 - viewProj.m21;
    frus.planes[3].y = viewProj.m42 - viewProj.m22;
    frus.planes[3].z = viewProj.m43 - viewProj.m23;
    frus.planes[3].w = viewProj.m44 - viewProj.m24;
    frus.planes[3].Normalize();

    // NEAR
    frus.planes[4].x = viewProj.m41 + viewProj.m31;
    frus.planes[4].y = viewProj.m42 + viewProj.m32;
    frus.planes[4].z = viewProj.m43 + viewProj.m33;
    frus.planes[4].w = viewProj.m44 + viewProj.m34;
    frus.planes[4].Normalize();

    // FAR
    frus.planes[5].x = viewProj.m41 - viewProj.m31;
    frus.planes[5].y = viewProj.m42 - viewProj.m32;
    frus.planes[5].z = viewProj.m43 - viewProj.m33;
    frus.planes[5].w = viewProj.m44 - viewProj.m34;
    frus.planes[5].Normalize();

    return frus;
}
