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

Camera::Camera() :
    fov(50.0f),
    aspect(1.333f),
    zNear(0.1f),
    zFar(100.0f)
{
    UpdateProjection();
}

void Camera::SetParameters(float fov, float zNear, float zFar)
{
    this->fov = fov;
    this->zNear = zNear;
    this->zFar = zFar;
    UpdateProjection();
}

void Camera::SetAspectRatio(float aspect)
{
    this->aspect = aspect;
    UpdateProjection();
}

const Matrix4 &Camera::GetProjection() const
{
    return projection;
}

void Camera::UpdateProjection()
{
    projection = Matrix4::Perspective(fov, aspect, zNear, zFar);
}

} // Scene
