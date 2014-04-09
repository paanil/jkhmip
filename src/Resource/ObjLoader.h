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

class ObjLoader
{
public:
    ObjLoader();

    Model *Load(const String &file);

private:
    struct Index
    {
        uint positionIndex;
        uint texcoordIndex;
        uint normalIndex;

        bool operator==(const Index &index) const
        {
            return ((positionIndex == index.positionIndex) &&
                    (texcoordIndex == index.texcoordIndex) &&
                    (normalIndex == index.normalIndex));
        }
    };

    String TakeIdent(const String &line, String &ident);

    bool ParseVector2(const String &line, Vector2 &v);
    bool ParseVector3(const String &line, Vector3 &v);

    bool ParsePosition(const String &line);
    bool ParseTexCoord(const String &line);
    bool ParseNormal(const String &line);

    bool ParseIndex(std::stringstream &ss, Index &index, bool verbose = true);
    bool ParseFace(const String &line);

//    void CreateSubMesh(const String &material);
//
//    void FinishLastSubMesh();

    void PushVector2(std::vector<float> &verts, const Vector2 &v);
    void PushVector3(std::vector<float> &verts, const Vector3 &v);

    bool BuildMeshData(std::vector<float> &meshVerts, std::vector<uint> &meshIndices);

private:
    std::vector<Vector3> positions;
    std::vector<Vector2> texcoords;
    std::vector<Vector3> normals;
    std::vector<Index>   indices;

//    std::vector<SubMesh> submeshes;
};

#endif // __OBJLOADER_H__
