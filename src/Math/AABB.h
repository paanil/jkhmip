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

#ifndef __AABB_H__
#define __AABB_H__

#include "Vector3.h"
#include "Matrix4.h"

class AABB
{
public:
    Vector3 min, max;

    AABB();

    void Update(const Vector3 &v);
    void Update(const AABB &aabb);

    AABB Transform(const Matrix4 &mat) const;
    Matrix4 CreateOrthoProjection() const;

    static AABB Degenerate();
    static AABB Intersection(const AABB &a, const AABB &b);
};

#endif // __AABB_H__
