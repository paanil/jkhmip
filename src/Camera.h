
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
