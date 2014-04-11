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
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include <GL/glew.h>

Model::Model() :
    vertexBuffer(0),
    indexBuffer(0)
{
}

Model::~Model()
{
    delete vertexBuffer;
    delete indexBuffer;
}

void Model::SetBuffers(VertexBuffer *vertexBuf, IndexBuffer *indexBuf)
{
    vertexBuffer = vertexBuf;
    indexBuffer = indexBuf;
}

void Model::AddSubMesh(uint firstIndex, uint indexCount, Texture *texture)
{
    SubMesh submesh;
    submesh.firstIndex = firstIndex;
    submesh.indexCount = indexCount;
    submesh.texture = texture;
    submeshes.push_back(submesh);
}

void Model::Render()
{
    if (vertexBuffer && indexBuffer)
    {
        vertexBuffer->Bind();
        indexBuffer->Bind();
        for (size_t i = 0; i < submeshes.size(); i++)
        {
            if (submeshes[i].texture) submeshes[i].texture->Bind(0);
            indexBuffer->DrawTriangles(submeshes[i].firstIndex, submeshes[i].indexCount);
        }
    }
}
