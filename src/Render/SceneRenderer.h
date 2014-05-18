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
#include "FrameBuffer.h"
#include "UniformBuffer.h"
#include "../Scene/Object.h"
#include "../Scene/Light.h"

#include <memory>

namespace Scene
{
    class Scene;
    class Camera;
}

class Shader;

class SceneRenderer
{
    typedef std::unique_ptr<FrameBuffer> FrameBufferPtr;
    typedef std::unique_ptr<UniformBuffer> UniformBufferPtr;

public:
    SceneRenderer();

    void Init(Shader *depthShader);

    void SetViewport(int x, int y, int w, int h);
    void SetCamera(Scene::Camera *camera);

    void UpdateShadowMaps(Scene::Scene &scene);
    void Render(Scene::Scene &scene);

    size_t GetObjectCount() const { return objects.size(); }
    size_t GetLightCount() const { return lights.size(); }
    size_t GetDrawCount() const { return commands.Size(); }

private:
    int vpX, vpY, vpW, vpH;
    Scene::Camera *   camera;
    Shader *          depthShader;
    FrameBufferPtr    shadowFBO;
    UniformBufferPtr  lightsUBO;

    Scene::ObjectList objects;
    Scene::LightList  lights;
    Scene::ObjectList objectsInLight;
    RenderCommandList commands;
};

#endif // __SCENERENDERER_H__
