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

class Material;
class VertexBuffer;
class IndexBuffer;

struct RenderCommand
{
    Material *material;
    VertexBuffer *vbo;
    IndexBuffer *ibo;
    uint firstIndex;
    uint indexCount;
    Matrix4 transform;
};

class RenderCommandList
{
public:
    void SetMaterial(Material *material) { command.material = material; }
    void SetVertexBuffer(VertexBuffer *vbo) { command.vbo = vbo; }
    void SetIndexBuffer(IndexBuffer *ibo) { command.ibo = ibo; }
    void SetTransform(const Matrix4 &transform) { command.transform = transform; }

    void AddRenderCommand(uint firstIndex, uint indexCount)
    {
        command.firstIndex = firstIndex;
        command.indexCount = indexCount;
        commands.push_back(command);
    }

    void Clear() { commands.clear(); }

    std::vector<RenderCommand>::iterator begin() { return commands.begin(); }
    std::vector<RenderCommand>::iterator end() { return commands.end(); }

private:
    RenderCommand command;

    std::vector<RenderCommand> commands;
};

#endif // __RENDERCOMMAND_H__
