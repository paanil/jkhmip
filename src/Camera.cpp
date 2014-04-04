
#include "Camera.h"

Camera::Camera()
{
    projection = Matrix4::Identity();
    transformation = Matrix4::Identity();
}

void Camera::SetOrthoProjection(float w, float h, float zNear, float zFar)
{
    projection = Matrix4::Ortho(w, h, zNear, zFar);
}

void Camera::SetOrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar);
{
    projection = Matrix4::Ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
    projection = Matrix4::Perspective(fov, aspect, zNear, zFar);
}

Matrix4 Camera::GetProjection() const
{
    return projection;
}

void Camera::SetPosition(const Vector3 &pos)
{
    transformation.m14 = pos.x;
    transformation.m24 = pos.y;
    transformation.m34 = pos.z;
}

Vector3 Camera::GetPosition() const
{
    const Matrix4 &tm = transformation;
    return Vector3(tm.m14, tm.m24, tm.m34);
}

void Camera::SetRotation(const Matrix3 &rot)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            transformation.mat[i][j] = rot.mat[i][j];
        }
    }
}

Matrix3 Camera::GetRotation() const
{
    Matrix3 rot;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rot.mat[i][j] = transformation.mat[i][j];
        }
    }
    return rot;
}

void Camera::GetRotationAxes(Vector3 &right, Vector3 &up, Vector3 &look) const
{
    const Matrix4 &tm = transformation;

    right = Vector3(tm.m11, tm.m21, tm.m31);
    up = Vector3(tm.m12, tm.m22, tm.m32);
    look = Vector3(tm.m13, tm.m23, tm.m33);
}

Matrix4 Camera::GetViewMatrix() const
{
    return transformation.InverseTR();
}
