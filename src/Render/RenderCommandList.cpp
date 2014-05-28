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

#include "RenderCommandList.h"

void RenderCommandList::ResetLights()
{
    command.lightCount = 0;
}

bool RenderCommandList::AddLight(Scene::Light *light)
{
    if (command.lightCount < MAX_LIGHTS)
    {
        Matrix4 bias = Matrix4::Translation(0.5f, 0.5f, 0.5f) * Matrix4::Scale(0.5f);
        Texture *shadowMap = light->GetShadowMap();

        int i = command.lightCount++;

        command.lights[i].type = light->GetType();
        command.lights[i].pos = light->GetPos();
        command.lights[i].dir = light->GetDir();
        command.lights[i].radius = light->GetRadius();
        command.lights[i].cutoff = light->GetCutoff();
        command.lights[i].color = light->GetColor();
        command.lights[i].energy = light->GetEnergy();
        command.lights[i].shadowRes = light->GetShadowRes();
        command.lights[i].noShadows = shadowMap ? 0.0f : 1.0f;
        command.lightMatrix[i] = bias * light->GetMatrix();
        command.shadowMaps[i] = shadowMap;

        return (command.lightCount == MAX_LIGHTS);
    }
    return true;
}

void RenderCommandList::SetModelMatrix(const Matrix4 &modelMatrix)
{
    command.modelMatrix = modelMatrix;
}

void RenderCommandList::SetMaterial(Material *material)
{
    command.material = material;
}

void RenderCommandList::SetVertexBuffer(VertexBuffer *vbo)
{
    command.vbo = vbo;
}

void RenderCommandList::SetIndexBuffer(IndexBuffer *ibo)
{
    command.ibo = ibo;
}

void RenderCommandList::AddRenderCommand(uint firstIndex, uint indexCount)
{
    command.firstIndex = firstIndex;
    command.indexCount = indexCount;
    commands.push_back(command);
}

size_t RenderCommandList::Size() const
{
    return commands.size();
}

void RenderCommandList::Clear()
{
    commands.clear();
}

RenderCommand &RenderCommandList::operator[](int i)
{
    return commands[i];
}

RenderCommandList::CommandList::iterator RenderCommandList::begin()
{
    return commands.begin();
}

RenderCommandList::CommandList::iterator RenderCommandList::end()
{
    return commands.end();
}
