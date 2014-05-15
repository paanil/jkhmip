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

#ifndef __RENDERCOMMAND_H__
#define __RENDERCOMMAND_H__

#include "../Scene/Light.h"
#include "../Math/Matrix4.h"
#include "../Types.h"

#include <vector>

#define MAX_LIGHTS 8

class Material;
class VertexBuffer;
class IndexBuffer;

struct RenderCommand
{
    Vector4 lightPosition[MAX_LIGHTS];
    Vector4 lightColor[MAX_LIGHTS];
    Matrix4 lightMatrix[MAX_LIGHTS];
    Texture *shadowMap[MAX_LIGHTS];
    Matrix4 modelMatrix;
    Material *material;
    VertexBuffer *vbo;
    IndexBuffer *ibo;
    uint firstIndex;
    uint indexCount;
};

class RenderCommandList
{
    typedef std::vector<RenderCommand> CommandList;

public:
    void ResetLights()
    {
        lightCount = 0;
        for (int i = 0; i < MAX_LIGHTS; i++)
        {
            command.lightColor[i].w = 0.0f;
            command.shadowMap[i] = 0;
        }
    }

    bool AddLight(Scene::Light *light)
    {
        if (lightCount < MAX_LIGHTS)
        {
            Matrix4 bias = Matrix4::Translation(0.5f, 0.5f, 0.5f) * Matrix4::Scale(0.5f);

            command.lightPosition[lightCount] = light->GetLightPos();
            command.lightColor[lightCount] = light->GetColor();
            command.lightMatrix[lightCount] = bias * light->GetLightMatrix();
            command.shadowMap[lightCount] = light->GetShadowMap();
            return (++lightCount >= MAX_LIGHTS);
        }
        return true;
    }

    void SetModelMatrix(const Matrix4 &modelMatrix) { command.modelMatrix = modelMatrix; }
    void SetMaterial(Material *material) { command.material = material; }
    void SetVertexBuffer(VertexBuffer *vbo) { command.vbo = vbo; }
    void SetIndexBuffer(IndexBuffer *ibo) { command.ibo = ibo; }

    void AddRenderCommand(uint firstIndex, uint indexCount)
    {
        command.firstIndex = firstIndex;
        command.indexCount = indexCount;
        commands.push_back(command);
    }

    size_t Size() const { return commands.size(); }
    void Clear() { commands.clear(); }

    CommandList::iterator begin() { return commands.begin(); }
    CommandList::iterator end() { return commands.end(); }

private:
    int lightCount;
    RenderCommand command;
    CommandList commands;
};

#endif // __RENDERCOMMAND_H__
