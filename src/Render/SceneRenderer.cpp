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

void SceneRenderer::Render(Scene::Scene &scene)
{
    Matrix4 proj = camera->GetProjection();
    Matrix4 view = camera->GetInverseWorldTransform();
    Frustum frus = Frustum::Extract(proj * view);

    objects.clear();
    lights.clear();
    scene.FrustumCull(frus, objects, &lights);

    AABB aabb = AABB::Degenerate();
    for (Scene::Object *object : objects)
        aabb.Update(object->GetWorldAABB());

    for (Scene::Light *light : lights)
    {
        if (light->GetRadius() > 0.0f) continue;

        light->UpdateLightMatrix(aabb);

        Matrix4 lightMatrix = light->GetLightMatrix();
//        Frustum frus2 = Frustum::Extract(lightMatrix);
        Texture *shadowMap = light->GetShadowMap();
        if (shadowMap == 0)
        {
            light->CreateShadowMap(1024, 1024);
            shadowMap = light->GetShadowMap();
        }
        int w = shadowMap->GetWidth();
        int h = shadowMap->GetHeight();

//        Scene::ObjectList objects2;
//        scene.FrustumCull(frus2, objects2);

//        aabb = AABB::Degenerate();
        commands.Clear();
        for (Scene::Object *object : objects)
        {
//            aabb.Update(object->GetWorldAABB());
            object->GetRenderCommands(commands);
        }

//        light->UpdateLightMatrix(aabb);
//        lightMatrix = light->GetLightMatrix();

        shadowFBO->AttachDepthTex2D(shadowMap);
        shadowFBO->Bind(true);

//        glClearDepth(1.0f);

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

    commands.Clear();
    for (Scene::Object *object : objects)
    {
        commands.ResetLights();
        for (Scene::Light *light : lights)
        {
            if (light->Affects(object->GetWorldAABB()) &&
                commands.AddLight(light))
                break;
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
        shader->SetUniform("Projection", proj);
        shader->SetUniform("View", view);
        shader->SetUniform("Model", command.modelMatrix);
        shader->SetUniform("LightPosition", MAX_LIGHTS, command.lightPosition);
        shader->SetUniform("LightColor", MAX_LIGHTS, command.lightColor);
        shader->SetUniform("LightMatrix", MAX_LIGHTS, command.lightMatrix);
        for (int i = 0; i < MAX_LIGHTS; i++)
            Graphics::SetTexture(command.shadowMap[i], 1 + i);
        Graphics::SetTexture(command.material->GetTexture(), 0);
        Graphics::SetVertexBuffer(command.vbo);
        Graphics::SetIndexBuffer(command.ibo);
        Graphics::DrawTriangles(command.firstIndex, command.indexCount);
    }
}
