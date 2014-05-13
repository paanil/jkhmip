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

#include "../Math/Matrix4.h"
#include "../Types.h"

#include <vector>

#define MAX_LIGHTS 8

class Material;
class VertexBuffer;
class IndexBuffer;

struct RenderCommand
{
    int lightCount;
    Vector4 lightPosition[MAX_LIGHTS];
    Vector4 lightColor[MAX_LIGHTS];
    Matrix4 transform;
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
        for (int i = 0; i < MAX_LIGHTS; i++)
            command.lightColor[i].w = 0.0f;
    }

    bool AddLight(const Vector4 &pos, const Vector4 &color)
    {
        if (command.lightCount < MAX_LIGHTS)
        {
            command.lightPosition[command.lightCount] = pos;
            command.lightColor[command.lightCount] = color;
            command.lightCount++;
        }
        return command.lightCount >= MAX_LIGHTS;
    }

    void SetTransform(const Matrix4 &transform) { command.transform = transform; }
    void SetMaterial(Material *material) { command.material = material; }
    void SetVertexBuffer(VertexBuffer *vbo) { command.vbo = vbo; }
    void SetIndexBuffer(IndexBuffer *ibo) { command.ibo = ibo; }

    void AddRenderCommand(uint firstIndex, uint indexCount)
    {
        command.firstIndex = firstIndex;
        command.indexCount = indexCount;
        commands.push_back(command);
    }

    size_t Size() { return commands.size(); }
    void Clear() { commands.clear(); }

    CommandList::iterator begin() { return commands.begin(); }
    CommandList::iterator end() { return commands.end(); }

private:
    RenderCommand command;
    CommandList commands;
};

#endif // __RENDERCOMMAND_H__
