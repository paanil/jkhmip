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

void Frustum::Construct(float fov, float aspect, float zNear, float zFar)
{
    fov *= Math::DEG_TO_RAD * 0.5f;
    float si = Math::Sin(fov);
    float co = Math::Cos(fov);

    planes[0] = Vector4(co, 0.0f, si*aspect, 0.0f);
    planes[1] = Vector4(-co, 0.0f, si*aspect, 0.0f);
    planes[2] = Vector4(0.0f, co, si, 0.0f);
    planes[3] = Vector4(0.0f, -co, si, 0.0f);
    planes[4] = Vector4(0.0f, 0.0f, 1.0f, zNear);
    planes[5] = Vector4(0.0f, 0.0f, -1.0f, zFar);
}

Frustum Frustum::Transformed(const Matrix4 &M) const
{
    Frustum F;
    for (int i = 0; i < 6; i++)
    {
        F.planes[i] = M * Vector4(planes[i].x, planes[i].y, planes[i].z, 0.0f);
        F.planes[i].w = planes[i].w - Vector4(M.m14, M.m24, M.m34, 0.0f).Dot(F.planes[i]);
        F.planes[i].Normalize();
    }
    return F;
}

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
