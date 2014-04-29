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

#ifndef __MODEL_H__
#define __MODEL_H__

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>
#include <vector>

class Material;

class SceneNode;
class SceneCamera;

/// Model class.
///
class Model
{
    typedef std::unique_ptr<VertexBuffer> VertexBufferPtr;
    typedef std::unique_ptr<IndexBuffer> IndexBufferPtr;

public:
    /// Sets vertex and index buffers and clears sub meshes.
    /// Releases old vertex and index buffers and takes ownership of the new ones.
    void SetBuffers(VertexBuffer *vertexBuf, IndexBuffer *indexBuf);
    /// Adds sub mesh with given material.
    void AddSubMesh(uint firstIndex, uint indexCount, Material *material);

    /// Renders the model.
    void Render(SceneNode *node, SceneCamera *camera);

private:
    /// Sub mesh is just a range of indices and a material.
    struct SubMesh
    {
        uint firstIndex;
        uint indexCount;
        Material *material;
    };

    VertexBufferPtr vertexBuffer;
    IndexBufferPtr indexBuffer;
    std::vector<SubMesh> submeshes;
};

#endif // __MODEL_H__
