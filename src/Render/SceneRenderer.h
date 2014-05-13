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

#ifndef __SCENERENDERER_H__
#define __SCENERENDERER_H__

#include "RenderCommand.h"
#include "../Scene/Object.h"
#include "../Scene/Light.h"

namespace Scene
{
    class Scene;
    class Camera;
}

class SceneRenderer
{
public:
    SceneRenderer();

    void SetViewport(int x, int y, int w, int h);
    void SetCamera(Scene::Camera *camera);

    void Render(Scene::Scene &scene);

private:
    int vpX, vpY, vpW, vpH;
    Scene::Camera *camera;

    Scene::ObjectList objects;
    Scene::LightList lights;
    RenderCommandList commands;
};

#endif // __SCENERENDERER_H__
