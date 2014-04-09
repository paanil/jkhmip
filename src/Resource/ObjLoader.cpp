
#include "ObjLoader.h"
#include "../Render/Model.h"
#include "../Logger.h"

#include <fstream>
#include <sstream>

ObjLoader::ObjLoader()
{
    // make some memory reservations so less allocs later
    positions.reserve(1000);
    texcoords.reserve(1000);
    normals.reserve(1000);
    indices.reserve(3000); // 1000 triangles
}

Model *ObjLoader::Load(const String &file)
{
    positions.clear();
    texcoords.clear();
    normals.clear();
    indices.clear();

    std::ifstream f(file);

    LOG_INFO("Loading model '%'...", file);

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        return 0;
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

        line = TakeIdent(line, ident);

        if (ident == "v")
            parseStatus = ParsePosition(line);
        else if (ident == "vt")
            parseStatus = ParseTexCoord(line);
        else if (ident == "vn")
            parseStatus = ParseNormal(line);
        else if (ident == "f")
            parseStatus = ParseFace(line);
        else if (ident == "usemtl")
            ; // TODO: create submesh

        if (!parseStatus)
        {
            LOG_ERROR("Loading model failed.");
            return 0;
        }
    }

    Model *model = new Model();
    if (!BuildMeshData(model->vertices, model->indices))
    {
        LOG_ERROR("Loading model failed.");
        delete model;
        return 0;
    }
    model->vertSize = 8;
    return model;
}

String ObjLoader::TakeIdent(const String &line, String &ident)
{
    ident.clear();

    size_t i = 0;
    for (; isalpha(line[i]); i++)
        ident.push_back(line[i]);
    for (; isspace(line[i]); i++) ; // skip whitespaces

    return line.substr(i); // return the rest of the line
}

bool ObjLoader::ParseVector2(const String &line, Vector2 &v)
{
    std::stringstream ss(line);
    return ((ss >> v.x) && (ss >> v.y));
}

bool ObjLoader::ParseVector3(const String &line, Vector3 &v)
{
    std::stringstream ss(line);
    return ((ss >> v.x) && (ss >> v.y) && (ss >> v.z));
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

bool ObjLoader::ParseIndex(std::stringstream &ss, Index &index, bool verbose)
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

//void ObjLoader::CreateSubMesh(const String &material)
//{
//    if (!submeshes.empty())
//    {
//        FinishLastSubMesh();
//    }
//
//    SubMesh submesh;
//    submesh.texture = materail;
//    submesh.firstIndex = indices.size();
//    submeshes.push_back(submesh);
//}
//
//void ObjLoader::FinishLastSubMesh()
//{
//    submeshes.back().indexCount =
//        indices.size() - submeshes.back().firstIndex;
//}

void ObjLoader::PushVector2(std::vector<float> &verts, const Vector2 &v)
{
    verts.push_back(v.x);
    verts.push_back(v.y);
}

void ObjLoader::PushVector3(std::vector<float> &verts, const Vector3 &v)
{
    verts.push_back(v.x);
    verts.push_back(v.y);
    verts.push_back(v.z);
}

bool ObjLoader::BuildMeshData(std::vector<float> &meshVerts, std::vector<uint> &meshIndices)
{
    std::vector<Index> uniques;
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

    return true;
}
