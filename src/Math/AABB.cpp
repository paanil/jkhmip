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

#include "AABB.h"
#include "Math.h"

AABB::AABB() :
    min(0.0f, 0.0f, 0.0f),
    max(0.0f, 0.0f, 0.0f)
{
}

void AABB::Update(const Vector3 &v)
{
    min.x = Math::Min(min.x, v.x);
    min.y = Math::Min(min.y, v.y);
    min.z = Math::Min(min.z, v.z);
    max.x = Math::Max(max.x, v.x);
    max.y = Math::Max(max.y, v.y);
    max.z = Math::Max(max.z, v.z);
}

void AABB::Update(const AABB &aabb)
{
    Update(aabb.min);
    Update(aabb.max);
}

AABB AABB::Transform(const Matrix4 &mat) const
{
    AABB aabb = AABB::Degenerate();
    aabb.Update(mat * Vector3(min.x, min.y, min.z));
    aabb.Update(mat * Vector3(min.x, min.y, max.z));
    aabb.Update(mat * Vector3(min.x, max.y, min.z));
    aabb.Update(mat * Vector3(min.x, max.y, max.z));
    aabb.Update(mat * Vector3(max.x, min.y, min.z));
    aabb.Update(mat * Vector3(max.x, min.y, max.z));
    aabb.Update(mat * Vector3(max.x, max.y, min.z));
    aabb.Update(mat * Vector3(max.x, max.y, max.z));
    return aabb;
}

Matrix4 AABB::CreateOrthoProjection() const
{
    return Matrix4::Ortho(min.x, max.x, min.y, max.y, min.z, max.z);
}

AABB AABB::Degenerate()
{
    AABB aabb;

    aabb.min = Vector3(Math::FLOAT_MAX, Math::FLOAT_MAX, Math::FLOAT_MAX);
    aabb.max = Vector3(Math::FLOAT_MIN, Math::FLOAT_MIN, Math::FLOAT_MIN);

    return aabb;
}

AABB AABB::Intersection(const AABB &a, const AABB &b)
{
    AABB aabb;

    aabb.min.x = Math::Max(a.min.x, b.min.x);
    aabb.min.y = Math::Max(a.min.y, b.min.y);
    aabb.min.z = Math::Max(a.min.z, b.min.z);
    aabb.max.x = Math::Min(a.max.x, b.max.x);
    aabb.max.y = Math::Min(a.max.y, b.max.y);
    aabb.max.z = Math::Min(a.max.z, b.max.z);

    return aabb;
}
