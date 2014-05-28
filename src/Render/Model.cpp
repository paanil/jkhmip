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

#include "Model.h"
#include "RenderCommandList.h"

#include <GL/glew.h>

void Model::SetAABB(const AABB &aabb)
{
    this->aabb = aabb;
}

const AABB &Model::GetAABB() const
{
    return aabb;
}

void Model::SetBuffers(VertexBuffer *vertexBuf, IndexBuffer *indexBuf)
{
    vertexBuffer.reset(vertexBuf);
    indexBuffer.reset(indexBuf);
    submeshes.clear();
}

void Model::AddSubMesh(uint firstIndex, uint indexCount, Material *material)
{
    SubMesh submesh;
    submesh.firstIndex = firstIndex;
    submesh.indexCount = indexCount;
    submesh.material = material;
    submeshes.push_back(submesh);
}

void Model::GetRenderCommands(RenderCommandList &commands)
{
    commands.SetVertexBuffer(vertexBuffer.get());
    commands.SetIndexBuffer(indexBuffer.get());

    for (SubMesh &submesh : submeshes)
    {
        commands.SetMaterial(submesh.material);
        commands.AddRenderCommand(submesh.firstIndex, submesh.indexCount);
    }
}
