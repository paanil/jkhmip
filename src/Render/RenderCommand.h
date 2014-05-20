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
    struct LightInfo
    {
        Vector3 type;
        Vector3 pos;
        Vector3 dir;
        float   radius;
        float   cutoff;
        Vector3 color;
        float   energy;
        Matrix4 matrix;
        float   noShadows;
    };

    int lightCount;
    LightInfo lights[MAX_LIGHTS];
    Texture *shadowMaps[MAX_LIGHTS];
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
        command.lightCount = 0;
    }

    bool AddLight(Scene::Light *light)
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
            command.lights[i].matrix = (bias * light->GetMatrix()).Transposed();
            command.lights[i].noShadows = shadowMap ? 0.0f : 1.0f;
            command.shadowMaps[i] = shadowMap;

            return (command.lightCount == MAX_LIGHTS);
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
    RenderCommand command;
    CommandList commands;
};

#endif // __RENDERCOMMAND_H__
