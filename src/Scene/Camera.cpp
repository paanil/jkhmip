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

#include "Camera.h"

namespace Scene
{

Camera::Camera()
{
    projection = Matrix4::Identity();
}

void Camera::SetOrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar)
{
    projection = Matrix4::Ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
    projection = Matrix4::Perspective(fov, aspect, zNear, zFar);
    frustum.Construct(fov, aspect, zNear, zFar);
}

const Matrix4 &Camera::GetProjection() const
{
    return projection;
}

Frustum Camera::GetFrustum()
{
    return frustum.Transformed(GetWorldTransform());
}

} // Scene
