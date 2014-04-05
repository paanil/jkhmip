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

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Math/Matrix3.h"
#include "Math/Matrix4.h"

/// Camera class.
///
class Camera
{
public:
    Camera();

    void SetOrthoProjection(float w, float h, float zNear, float zFar);
    void SetOrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar);

    void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);

    Matrix4 GetProjection() const;

    void SetPosition(const Vector3 &pos);
    Vector3 GetPosition() const;

    void SetRotation(const Matrix3 &rot);
    Matrix3 GetRotation() const;

    void GetRotationAxes(Vector3 &right, Vector3 &up, Vector3 &look) const;

    Matrix4 GetViewMatrix() const;

private:
    Matrix4 projection;
    Matrix4 transformation;
};

#endif // __CAMERA_H__
