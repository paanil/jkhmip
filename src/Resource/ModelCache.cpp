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

#include "ModelCache.h"
#include "../Render/VertexBuffer.h"#include "../Render/IndexBuffer.h"
#include "../Logger.h"

ModelCache::ModelCache(TextureCache &texCache) :
    textureCache(texCache)
{
}

Model *ModelCache::Load(const String &filePath)
{
    Model *model = new Model();

    if (!loader.Load(filePath, *model, textureCache))
    {
        LOG_INFO("Using debug model.");
        MakeCube(*model);
    }

    return model;
}

void ModelCache::MakeCube(Model &model)
{
    static const float radius = 1.0f;

    static const float verts[24][6] =
    {
        // LEFT
        {-radius, -radius, -radius, -1.0f, 0.0f, 0.0f},
        {-radius,  radius, -radius, -1.0f, 0.0f, 0.0f},
        {-radius,  radius,  radius, -1.0f, 0.0f, 0.0f},
        {-radius, -radius,  radius, -1.0f, 0.0f, 0.0f},
        // RIGHT
        { radius, -radius, -radius,  1.0f, 0.0f, 0.0f},
        { radius,  radius, -radius,  1.0f, 0.0f, 0.0f},
        { radius,  radius,  radius,  1.0f, 0.0f, 0.0f},
        { radius, -radius,  radius,  1.0f, 0.0f, 0.0f},
        // BOTTOM
        {-radius, -radius, -radius, 0.0f, -1.0f, 0.0f},
        {-radius, -radius,  radius, 0.0f, -1.0f, 0.0f},
        { radius, -radius,  radius, 0.0f, -1.0f, 0.0f},
        { radius, -radius, -radius, 0.0f, -1.0f, 0.0f},
        // TOP
        {-radius,  radius, -radius, 0.0f,  1.0f, 0.0f},
        {-radius,  radius,  radius, 0.0f,  1.0f, 0.0f},
        { radius,  radius,  radius, 0.0f,  1.0f, 0.0f},
        { radius,  radius, -radius, 0.0f,  1.0f, 0.0f},
        // BACK
        {-radius, -radius, -radius, 0.0f, 0.0f, -1.0f},
        {-radius,  radius, -radius, 0.0f, 0.0f, -1.0f},
        { radius,  radius, -radius, 0.0f, 0.0f, -1.0f},
        { radius, -radius, -radius, 0.0f, 0.0f, -1.0f},
        // FRONT
        {-radius, -radius,  radius, 0.0f, 0.0f,  1.0f},
        {-radius,  radius,  radius, 0.0f, 0.0f,  1.0f},
        { radius,  radius,  radius, 0.0f, 0.0f,  1.0f},
        { radius, -radius,  radius, 0.0f, 0.0f,  1.0f},
    };

    static const uint faces[12][3] =
    {
        { 0,  3,  2}, { 2,  1,  0}, // LEFT
        { 4,  5,  6}, { 6,  7,  4}, // RIGHT
        { 8, 11, 10}, {10,  9,  8}, // BOTTOM
        {12, 13, 14}, {14, 15, 12}, // TOP
        {16, 17, 18}, {18, 19, 16}, // BACK
        {20, 23, 22}, {22, 21, 20}, // FRONT
    };

    static const uint vertSize = 6*sizeof(float);

    VertexBuffer *vertexBuf = new VertexBuffer();
    IndexBuffer *indexBuf = new IndexBuffer();

    vertexBuf->SetData(24*vertSize, verts);
    vertexBuf->SetAttribute(VA_POSITION, vertSize, 0);
    vertexBuf->SetAttribute(VA_NORMAL, vertSize, &((float *)0)[3]);
    indexBuf->SetData(12*3*sizeof(uint), faces);

    model.SetBuffers(vertexBuf, indexBuf);
    model.AddSubMesh(0, 12*3, 0);
}
