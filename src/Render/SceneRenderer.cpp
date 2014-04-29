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
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneCamera.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

void SceneRenderer::Render(Scene &scene, SceneCamera *camera)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4 proj = camera->GetProjection();
    Matrix4 view = camera->GetInverseWorldTransform();

    commands.Clear();
    scene.GetRenderCommands(commands);

    for (RenderCommand &command : commands)
    {
        Shader *shader = command.material->GetShader();
        shader->Use();
        shader->SetProjMatrix(proj);
        shader->SetViewMatrix(view);
        shader->SetModelMatrix(command.transform);
        shader->SetTime(SDL_GetTicks() / 1000.0f);

        command.material->GetTexture()->Bind(0);

        command.vbo->Bind();
        command.ibo->Bind();
        command.ibo->DrawTriangles(command.firstIndex, command.indexCount);
    }
}
