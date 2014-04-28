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

#include "ObjLoader.h"
#include "../Render/VertexBuffer.h"
#include "../Render/IndexBuffer.h"
#include "../Render/Model.h"
#include "../Resource/TextureCache.h"
#include "../Logger.h"

#include <fstream>
#include <sstream>

// ----------------------------------------

String ParseIdent(const String &line, String &ident);
bool ParseVector2(const String &line, Vector2 &v);
bool ParseVector3(const String &line, Vector3 &v);
bool ParseIndex(std::stringstream &ss, ObjLoader::Index &index, bool verbose = true);
void PushVector2(std::vector<float> &verts, const Vector2 &v);
void PushVector3(std::vector<float> &verts, const Vector3 &v);

// ----------------------------------------

bool ObjLoader::Index::operator==(const Index &index) const
{
    return ((positionIndex == index.positionIndex) &&
            (texcoordIndex == index.texcoordIndex) &&
            (normalIndex == index.normalIndex));
}

// ----------------------------------------

/* ObjLoader */

ObjLoader::ObjLoader()
{
    // make some memory reservations so less allocs later
    positions.reserve(1000);
    texcoords.reserve(1000);
    normals.reserve(1000);
    indices.reserve(3000); // 1000 triangles
}

bool ObjLoader::Load(const String &file, Model &model, TextureCache *textureCache)
{
    LOG_INFO("Loading model '%'...", file);

    positions.clear();
    texcoords.clear();
    normals.clear();
    indices.clear();

    std::ifstream f(file);

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        return false;
    }

    String line;
    String ident;
    bool parseStatus = true;

    while (std::getline(f, line))
    {
        if (line.empty())
            continue; // skip empty lines
        if (line[0] == '#')
            continue; // skip comments

        line = ParseIdent(line, ident);

        if (ident == "v")
            parseStatus = ParsePosition(line);
        else if (ident == "vt")
            parseStatus = ParseTexCoord(line);
        else if (ident == "vn")
            parseStatus = ParseNormal(line);
        else if (ident == "f")
            parseStatus = ParseFace(line);
        else if (ident == "usemtl")
            AddSubMesh(line);

        if (!parseStatus)
            break;
    }

    if (submeshes.empty())
    {
        AddSubMesh("debug");
        submeshes.back().firstIndex = 0;
    }
    FinishLastSubMesh();

    if (!parseStatus || !BuildModel(model, textureCache))
    {
        LOG_ERROR("Loading model failed.");
        return false;
    }
    return true;
}

bool ObjLoader::ParsePosition(const String &line)
{
    Vector3 position;
    if (!ParseVector3(line, position))
    {
        LOG_ERROR("Invalid vertex position.");
        return false;
    }
    position.z *= -1.0f;
    positions.push_back(position);
    return true;
}

bool ObjLoader::ParseTexCoord(const String &line)
{
    Vector2 texcoord;
    if (!ParseVector2(line, texcoord))
    {
        LOG_ERROR("Invalid texture coordinate.");
        return false;
    }
    texcoords.push_back(texcoord);
    return true;
}

bool ObjLoader::ParseNormal(const String &line)
{
    Vector3 normal;
    if (!ParseVector3(line, normal))
    {
        LOG_ERROR("Invalid vertex normal.");
        return false;
    }
    normal.x *= -1.0f;
    normal.y *= -1.0f;
    normals.push_back(normal);
    return true;
}

bool ObjLoader::ParseFace(const String &line)
{
    Index index1, index2, index3, index4;
    std::stringstream ss(line);

    if (!ParseIndex(ss, index1))
        return false;

    if (!ParseIndex(ss, index2))
        return false;

    if (!ParseIndex(ss, index3))
        return false;

    // add a triangle
    indices.push_back(index1);
    indices.push_back(index2);
    indices.push_back(index3);

    if (ParseIndex(ss, index4, false))
    {
        // apparently a quad face
        // lets add another trianle
        indices.push_back(index1);
        indices.push_back(index3);
        indices.push_back(index4);

        if (ParseIndex(ss, index1, false))
        {
            LOG_ERROR("Only triangle and quad faces are supported.");
            return false;
        }
    }

    return true;
}

void ObjLoader::AddSubMesh(const String &material)
{
    if (!submeshes.empty())
    {
        FinishLastSubMesh();
    }

    SubMesh submesh;
    submesh.firstIndex = indices.size();
    submesh.material = material;
    submeshes.push_back(submesh);
}

void ObjLoader::FinishLastSubMesh()
{
    submeshes.back().indexCount =
        indices.size() - submeshes.back().firstIndex;
}

bool ObjLoader::BuildModel(Model &model, TextureCache *textureCache)
{
    std::vector<Index> uniques;
    std::vector<uint> meshIndices;
    uniques.reserve(indices.size());
    meshIndices.reserve(indices.size());

    for (size_t i = 0; i < indices.size(); i++)
    {
        uint index = uniques.size();
        for (size_t j = 0; j < uniques.size(); j++)
        {
            if (indices[i] == uniques[j])
            {
                index = j;
                break;
            }
        }
        if (index == uniques.size())
            uniques.push_back(indices[i]);
        meshIndices.push_back(index);
    }

    bool hasTexcoords = !texcoords.empty();
    bool hasNormals = !normals.empty();
    uint vertSize = 3 + (hasTexcoords ? 2 : 0) + (hasNormals ? 3 : 0);

    std::vector<float> meshVerts;
    meshVerts.reserve(uniques.size() * vertSize);

    for (size_t i = 0; i < uniques.size(); i++)
    {
        uint index = uniques[i].positionIndex;
        if (index == 0 || index > positions.size())
        {
            LOG_ERROR("Invalid vertex position index.");
            return false;
        }
        PushVector3(meshVerts, positions[index - 1]);
        if (hasTexcoords)
        {
            index = uniques[i].texcoordIndex;
            if (index == 0 || index > texcoords.size())
            {
                LOG_ERROR("Invalid texture coordinate index.");
                return false;
            }
            PushVector2(meshVerts, texcoords[index - 1]);
        }
        if (hasNormals)
        {
            index = uniques[i].normalIndex;
            if (index == 0 || index > normals.size())
            {
                LOG_ERROR("Invalid texture coordinate index.");
                return false;
            }
            PushVector3(meshVerts, normals[index - 1]);
        }
    }

    uint stride = vertSize * sizeof(float);

    VertexBuffer *vertBuf = new VertexBuffer();
    IndexBuffer *indexBuf = new IndexBuffer();

    vertBuf->SetData(meshVerts.size() * sizeof(float), &meshVerts[0]);
    indexBuf->SetData(meshIndices.size() * sizeof(uint), &meshIndices[0]);

    float *offs = 0;
    vertBuf->SetAttribute(VA_POSITION, stride, offs); offs += 3;
    if (hasTexcoords) { vertBuf->SetAttribute(VA_TEXCOORD, stride, offs); offs += 2; }
    if (hasNormals)   { vertBuf->SetAttribute(VA_NORMAL, stride, offs); offs += 3; }

    model.SetBuffers(vertBuf, indexBuf);

    for (size_t i = 0; i < submeshes.size(); i++)
    {
        const SubMesh &submesh = submeshes[i];
        Texture *texture = textureCache->Get(submesh.material);
        texture->SetFilterMode(TF_MIN_LINEAR_MIP_LINEAR, TF_MAG_LINEAR);
        texture->SetWrapMode(TW_REPEAT, TW_REPEAT);
        texture->GenMipmaps();
        model.AddSubMesh(submesh.firstIndex, submesh.indexCount, texture);
    }

    return true;
}

// ----------------------------------------

/* Free functions */

String ParseIdent(const String &line, String &ident)
{
    ident.clear();

    size_t i = 0;
    for (; isalpha(line[i]); i++)
        ident.push_back(line[i]);
    for (; isspace(line[i]); i++) ; // skip whitespaces

    return line.substr(i); // return the rest of the line
}

bool ParseVector2(const String &line, Vector2 &v)
{
    std::stringstream ss(line);
    return ((ss >> v.x) && (ss >> v.y));
}

bool ParseVector3(const String &line, Vector3 &v)
{
    std::stringstream ss(line);
    return ((ss >> v.x) && (ss >> v.y) && (ss >> v.z));
}

bool ParseIndex(std::stringstream &ss, ObjLoader::Index &index, bool verbose)
{
    index.positionIndex = 0;
    index.texcoordIndex = 0;
    index.normalIndex = 0;

    if (!(ss >> index.positionIndex))
    {
        if (verbose)
            LOG_ERROR("Invalid face definition: Vertex position required.");
        return false;
    }

    if (ss.get() == '/')
    {
        if (!(ss >> index.texcoordIndex))
            index.texcoordIndex = 0;

        if (ss.get() == '/')
        {
            if (!(ss >> index.normalIndex))
            {
                LOG_ERROR("Invalid face definition: Vertex normal expected.");
                index.normalIndex = 0;
                return false;
            }
        }
    }

    return true;
}

void PushVector2(std::vector<float> &verts, const Vector2 &v)
{
    verts.push_back(v.x);
    verts.push_back(v.y);
}

void PushVector3(std::vector<float> &verts, const Vector3 &v)
{
    verts.push_back(v.x);
    verts.push_back(v.y);
    verts.push_back(v.z);
}

// ----------------------------------------
