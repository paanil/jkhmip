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
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "../Scene/SceneCamera.h"

#include <GL/glew.h>

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

void Model::Render(SceneNode *node, SceneCamera *camera)
{
    if (vertexBuffer && indexBuffer)
    {
        vertexBuffer->Bind();
        indexBuffer->Bind();
        for (size_t i = 0; i < submeshes.size(); i++)
        {
            SubMesh &submesh = submeshes[i];
            Material *material = submesh.material;
            Shader *shader = material->GetShader();

            shader->Use();
            shader->SetProjMatrix(camera->GetProjection());
            shader->SetViewMatrix(camera->GetInverseWorldTransform());
            shader->SetModelMatrix(node->GetWorldTransform());
            material->GetTexture()->Bind(0);

            indexBuffer->DrawTriangles(submesh.firstIndex, submesh.indexCount);
        }
    }
}
