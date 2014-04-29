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

#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__

#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Types.h"

#include <vector>

class Model;
class MaterialCache;

/// Loader for Wavefront .obj files.
///
class ObjLoader
{
public:
    /// Obj vertex index.
    struct Index
    {
        uint positionIndex;
        uint texcoordIndex;
        uint normalIndex;

        /// Tests equality of two indices.
        bool operator==(const Index &index) const;
    };

public:
    /// Reserves some memory so less allocations when loading.
    ObjLoader();

    /// Loads .obj file into model. MaterialCache is needed to get the
    /// materials for the model. Returns false on fail.
    bool Load(const String &file, Model &model, MaterialCache *materialCache);

private:
    /// Parses vertex position (Vector3) from line.
    /// Returns false on fail.
    bool ParsePosition(const String &line);
    /// Parses texture coordinate (Vector2) from line.
    /// Returns false on fail.
    bool ParseTexCoord(const String &line);
    /// Parses vertex normal (Vector3) from line.
    /// Returns false on fail.
    bool ParseNormal(const String &line);

    /// Parses face indices from line.
    /// Line must contain at least 3 indices meaning a triangle.
    /// Faces with 4 indices (quad) are split into two triangles.
    /// Faces containing more than 4 indices are not supported.
    /// Returns false on fail.
    bool ParseFace(const String &line);

    /// Finishes last sub mesh and adds a new sub mesh with given material.
    /// Following faces belong to this sub mesh until new sub mesh is added.
    void AddSubMesh(const String &material);
    /// Finishes last sub mesh.
    void FinishLastSubMesh();

    /// Builds model from loaded data:
    /// creates proper vertex/index buffers and
    /// adds submeshes with loaded textures.
    bool BuildModel(Model &model, MaterialCache *materialCache);

private:
    /// Sub mesh.
    struct SubMesh
    {
        uint firstIndex;
        uint indexCount;
        String material;
    };

    std::vector<Vector3> positions;
    std::vector<Vector2> texcoords;
    std::vector<Vector3> normals;
    std::vector<Index>   indices;
    std::vector<SubMesh> submeshes;
};

#endif // __OBJLOADER_H__
