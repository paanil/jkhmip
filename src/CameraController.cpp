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

#include "CameraController.h"
#include "Scene/SceneCamera.h"
#include "Math/Math.h"

#include <SDL2/SDL.h>

CameraController::CameraController() :
    camera(0),
    cameraAngles(0.0f, 0.0f, 0.0f)
{
}

void CameraController::SetCamera(SceneCamera *camera)
{
    this->camera = camera;
}

void CameraController::Update(float dt)
{
    if (camera == 0)
        return;

    const Uint8 *keys = SDL_GetKeyboardState(0);

    const float speed = 6.0f;
    const float sensitivity = 0.25f;

    // Camera movement

    Vector3 pos = camera->GetPosition();
    Vector3 right, up, look;
    camera->GetBasisVectors(right, up, look);

    Vector3 dir(0.0f, 0.0f, 0.0f);

    if (keys[SDL_SCANCODE_W])
        dir += look;
    if (keys[SDL_SCANCODE_S])
        dir -= look;
    if (keys[SDL_SCANCODE_A])
        dir -= right;
    if (keys[SDL_SCANCODE_D])
        dir += right;

    float speedup = 1.0f;
    if (keys[SDL_SCANCODE_LSHIFT])
        speedup = 2.0f;

    dir.SafeNormalize();
    pos += dir * (speed * speedup * dt);

    camera->SetPosition(pos);

    // Camera rotation

    int relMouseX, relMouseY;
    if (SDL_GetRelativeMouseState(&relMouseX, &relMouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);

        cameraAngles.y += relMouseX * sensitivity;
        cameraAngles.x += relMouseY * sensitivity;
        cameraAngles.y = Math::WrapAngleDegrees(cameraAngles.y);
        cameraAngles.x = Math::Clamp(cameraAngles.x, -90.0f, 90.0f);

        Matrix3 rot = Matrix3::RotationYXZ(cameraAngles);
        camera->SetRotation(rot);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}
