
#ifndef __SCENECAMERA_H__
#define __SCENECAMERA_H__

#include "SceneNode.h"

class SceneCamera : public SceneNode
{
public:
    SceneCamera();

    void SetOrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar);
    void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);

    Matrix4 GetProjection() const;

private:
    Matrix4 projection;
};

#endif // __SCENECAMERA_H__
