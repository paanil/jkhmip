
#ifndef __CAMERACONTROLLER_H__
#define __CAMERACONTROLLER_H__

#include "Math/Vector3.h"

class SceneCamera;

class CameraController
{
public:
    CameraController();

    void SetCamera(SceneCamera *camera);

    void Update(float dt);

private:
    SceneCamera *camera;
    Vector3 cameraAngles;
};

#endif // __CAMERACONTROLLER_H__
