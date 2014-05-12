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
#include "Material.h"
#include "Shader.h"
#include "../Scene/Scene.h"
#include "Graphics.h"
#include "../Math/Frustum.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

int SceneRenderer::Render(Scene::Scene &scene, Scene::Camera *camera)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    Graphics::Clear(CLEAR_COLOR_AND_DEPTH);

    Matrix4 proj = camera->GetProjection();
    Matrix4 view = camera->GetInverseWorldTransform();
    Frustum frus = camera->GetFrustum();

    ObjectList objects;
    scene.FrustumCull(frus, objects);

    commands.Clear();
    for (Scene::Object *ob : objects)
    {
        Graphics::ResetState();
        Graphics::ApplyState();

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(proj.data);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(view.data);

        const AABB &aabb = ob->GetWorldAABB();

        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(aabb.min.x, aabb.min.y, aabb.min.z);
        glVertex3f(aabb.max.x, aabb.min.y, aabb.min.z);
        glVertex3f(aabb.max.x, aabb.max.y, aabb.min.z);
        glVertex3f(aabb.max.x, aabb.max.y, aabb.max.z);
        glVertex3f(aabb.min.x, aabb.max.y, aabb.max.z);
        glVertex3f(aabb.min.x, aabb.min.y, aabb.max.z);
        glVertex3f(aabb.min.x, aabb.min.y, aabb.min.z);
        glVertex3f(aabb.min.x, aabb.max.y, aabb.min.z);
        glVertex3f(aabb.max.x, aabb.max.y, aabb.min.z);
        glVertex3f(aabb.min.x, aabb.max.y, aabb.min.z);
        glVertex3f(aabb.min.x, aabb.max.y, aabb.max.z);
        glVertex3f(aabb.max.x, aabb.max.y, aabb.max.z);
        glVertex3f(aabb.max.x, aabb.min.y, aabb.max.z);
        glVertex3f(aabb.min.x, aabb.min.y, aabb.max.z);
        glVertex3f(aabb.max.x, aabb.min.y, aabb.max.z);
        glVertex3f(aabb.max.x, aabb.min.y, aabb.min.z);
        glEnd();

        ob->GetRenderCommands(commands);
    }

    for (RenderCommand &command : commands)
    {
        Graphics::ResetState();

        Graphics::SetTexture(command.material->GetTexture(), 0);

        Shader *shader = command.material->GetShader();
        Graphics::SetShader(shader);
        shader->SetProjMatrix(proj);
        shader->SetViewMatrix(view);
        shader->SetModelMatrix(command.transform);
        shader->SetTime(SDL_GetTicks() / 1000.0f);

        Graphics::SetVertexBuffer(command.vbo);
        Graphics::SetIndexBuffer(command.ibo);

        Graphics::DrawTriangles(command.firstIndex, command.indexCount);
    }

    return commands.Size();
}
