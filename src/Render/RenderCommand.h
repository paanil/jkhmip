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

#ifndef __RENDERCOMMAND_H__
#define __RENDERCOMMAND_H__

#include "../Math/Matrix4.h"
#include "../Types.h"

#define MAX_LIGHTS 8

class Material;
class VertexBuffer;
class IndexBuffer;
class Texture;

struct RenderCommand
{
    struct LightInfo
    {
        Vector3 type;
        Vector3 pos;
        float   radius;
        Vector3 dir;
        float   cutoff;
        Vector3 color;
        float   energy;
        float   shadowRes;
        float   noShadows;
    };

    int lightCount;
    LightInfo lights[MAX_LIGHTS];
    Matrix4 lightMatrix[MAX_LIGHTS];
    Texture *shadowMaps[MAX_LIGHTS];
    Matrix4 modelMatrix;
    Material *material;
    VertexBuffer *vbo;
    IndexBuffer *ibo;
    uint firstIndex;
    uint indexCount;
};

#endif // __RENDERCOMMAND_H__
