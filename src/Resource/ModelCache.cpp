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
#include "../Logger.h"

Model *ModelCache::Get(const String &file)
{
    auto it = resources.find(file);
    if (it != resources.end())
    {
        return it->second.get();
    }

    Model *model = loader.Load(direcotry + file);

    if (!model)
    {
        LOG_INFO("Using debug model.");
        model = MakeCube();
    }

    resources[file] = ResourcePtr(model);
    return model;
}

Model *ModelCache::MakeCube()
{
    const float radius = 1.0f;

    const float verts[24][6] =
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

    const uint faces[12][3] =
    {
        { 0,  3,  2}, { 2,  1,  0}, // LEFT
        { 4,  5,  6}, { 6,  7,  4}, // RIGHT
        { 8, 11, 10}, {10,  9,  8}, // BOTTOM
        {12, 13, 14}, {14, 15, 12}, // TOP
        {16, 17, 18}, {18, 19, 16}, // BACK
        {20, 23, 22}, {22, 21, 20}, // FRONT
    };

//    const uint vertSize = 6*sizeof(float);

    Model *model = new Model();
    for (int i = 0; i < 24; i++)
    {
        model->vertices.push_back(verts[i][0]);
        model->vertices.push_back(verts[i][1]);
        model->vertices.push_back(verts[i][2]);
        model->vertices.push_back(0.0f);
        model->vertices.push_back(0.0f);
        model->vertices.push_back(verts[i][3]);
        model->vertices.push_back(verts[i][4]);
        model->vertices.push_back(verts[i][5]);
    }
    for (int i = 0; i < 12; i++)
    {
        model->indices.push_back(faces[i][0]);
        model->indices.push_back(faces[i][1]);
        model->indices.push_back(faces[i][2]);
    }
    model->vertSize = 8;
    return model;

//    vertexBuf.SetData(24*vertSize, verts);
//    vertexBuf.SetAttribute(VA_POSITION, vertSize, 0);
//    vertexBuf.SetAttribute(VA_NORMAL, vertSize, &((float *)0)[3]);
//    indexBuf.SetData(12*3*sizeof(uint), faces);
//    indexRange.firstIndex = 0;
//    indexRange.indexCount = 12*3;
}
