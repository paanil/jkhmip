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

#include "SceneRenderer.h"
#include "Graphics.h"
#include "Material.h"
#include "Shader.h"
#include "../Scene/Scene.h"
#include "../Math/Frustum.h"

#include <SDL2/SDL.h>

#include "FrameBuffer.h"
#include "Texture.h"
#include "../Logger.h"
#include <GL/glew.h>

SceneRenderer::SceneRenderer() :
    vpX(0), vpY(0), vpW(800), vpH(600), camera(0)
{
}

void SceneRenderer::Init(Shader *depthShader)
{
    this->depthShader = depthShader;
    shadowFBO.reset(new FrameBuffer());
    lightsUBO.reset(new UniformBuffer());
    lightsUBO->ReserveData(sizeof(RenderCommand::lights));
}

void SceneRenderer::SetViewport(int x, int y, int w, int h)
{
    vpX = x;
    vpY = y;
    vpW = w;
    vpH = h;

    if (camera)
        camera->SetAspectRatio( float(w)/float(h) );
}

void SceneRenderer::SetCamera(Scene::Camera *camera)
{
    this->camera = camera;

    if (camera)
        camera->SetAspectRatio( float(vpW)/float(vpH) );
}

void SceneRenderer::UpdateShadowMaps(Scene::Scene &scene)
{
    AABB wholeScene = scene.GetBoundingBox();
    AABB visibleScene = AABB::Degenerate();
    for (Scene::Object *object : objects)
        visibleScene.Update(object->GetWorldAABB());

    for (Scene::Light *light : lights)
    {
        Texture *shadowMap = light->GetShadowMap();

        if (shadowMap == 0) continue;



        light->UpdateMatrix(visibleScene, wholeScene);

        Matrix4 lightMatrix = light->GetMatrix();
        Frustum frus = Frustum::Extract(lightMatrix);
        int w = shadowMap->GetWidth();
        int h = shadowMap->GetHeight();

        objectsInLight.clear();
        scene.FrustumCull(frus, objectsInLight);

        visibleScene = AABB::Degenerate();
        commands.Clear();
        for (Scene::Object *object : objectsInLight)
        {
            visibleScene.Update(object->GetWorldAABB());
            object->GetRenderCommands(commands);
        }

        light->UpdateMatrixNear(visibleScene);
        lightMatrix = light->GetMatrix();

        shadowFBO->AttachDepthTex2D(shadowMap);
        shadowFBO->Bind(true);

        Graphics::SetViewport(0, 0, w, h);
        Graphics::Clear(CLEAR_DEPTH);
        Graphics::ResetState();
        Graphics::SetShader(depthShader);
        depthShader->SetUniform("LightMatrix", lightMatrix);

        for (RenderCommand &command : commands)
        {
            depthShader->SetUniform("Model", command.modelMatrix);
            Graphics::SetVertexBuffer(command.vbo);
            Graphics::SetIndexBuffer(command.ibo);
            Graphics::DrawTriangles(command.firstIndex, command.indexCount);
        }

        shadowFBO->AttachDepthTex2D(0);
    }

    shadowFBO->Unbind();
}

void SceneRenderer::Render(Scene::Scene &scene)
{
    Matrix4 viewProj = camera->GetProjection() * camera->GetInverseWorldTransform();
    Frustum frus = Frustum::Extract(viewProj);

    objects.clear();
    lights.clear();
    scene.FrustumCull(frus, objects, &lights);

    UpdateShadowMaps(scene);

    commands.Clear();
    for (Scene::Object *object : objects)
    {
        commands.ResetLights();
        for (Scene::Light *light : lights)
        {
            if ( light->Affects(object->GetWorldAABB()) )
            {
                if (commands.AddLight(light)) break;
            }
        }
        object->GetRenderCommands(commands);
    }

    Graphics::SetViewport(vpX, vpY, vpW, vpH);
    Graphics::Clear(CLEAR_COLOR_AND_DEPTH);

    for (RenderCommand &command : commands)
    {
        Graphics::ResetState();

        Shader *shader = command.material->GetShader();
        Graphics::SetShader(shader);
        shader->SetUniform("ViewProj", viewProj);
        shader->SetUniform("Model", command.modelMatrix);

        lightsUBO->UpdateData(sizeof(RenderCommand::lights), command.lights);
        lightsUBO->Bind(0);

        for (int i = 0; i < MAX_LIGHTS; i++)
            Graphics::SetTexture(command.shadowMaps[i], 8 + i);
        for (int i = 0; i < MAX_MATERIAL_TEXTURES; i++)
            Graphics::SetTexture(command.material->GetTexture(i), i);

        Graphics::SetVertexBuffer(command.vbo);
        Graphics::SetIndexBuffer(command.ibo);
        Graphics::DrawTriangles(command.firstIndex, command.indexCount);
    }
}
