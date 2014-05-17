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
#include "../Math/Math.h"
#include "../Logger.h"

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

void Camera::GetFrustumCorners(Vector3 (&corners)[8], float zFar)
{
    const Matrix4 &m = GetWorldTransform();

    Vector3 r(m.m11, m.m21, m.m31);
    Vector3 u(m.m12, m.m22, m.m32);
    Vector3 l(m.m13, m.m23, m.m33);
    Vector3 p(m.m14, m.m24, m.m34);

    Vector3 centerN = p + l * zNear;
    Vector3 centerF = p + l * zFar;

    float t = Math::Tan(fov*0.5f*Math::DEG_TO_RAD);

    float h2 = t * zNear;
    float H2 = t * zFar;
    float w2 = h2 * aspect;
    float W2 = H2 * aspect;

    corners[0] = centerN - r*w2 - u*h2;
    corners[1] = centerN + r*w2 - u*h2;
    corners[2] = centerN - r*w2 + u*h2;
    corners[3] = centerN + r*w2 + u*h2;
    corners[4] = centerF - r*W2 - u*H2;
    corners[5] = centerF + r*W2 - u*H2;
    corners[6] = centerF - r*W2 + u*H2;
    corners[7] = centerF + r*W2 + u*H2;
}

void Camera::UpdateProjection()
{
    projection = Matrix4::Perspective(fov, aspect, zNear, zFar);
}

} // Scene
