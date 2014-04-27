
#include "SceneCamera.h"

SceneCamera::SceneCamera()
{
    projection = Matrix4::Identity();
}

void SceneCamera::SetOrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar)
{
    projection = Matrix4::Ortho(left, right, bottom, top, zNear, zFar);
}

void SceneCamera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
    projection = Matrix4::Perspective(fov, aspect, zNear, zFar);
}

Matrix4 SceneCamera::GetProjection() const
{
    return projection;
}
