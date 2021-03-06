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

#include "Font.h"
#include "../Render/TextGeometry.h"
#include "../Logger.h"

Font::Font() :
    vertices(MAX_TEXT_LENGTH * 4),
    indexBuffer(0),
    lineH(0), base(0),
    texW(0), texH(0),
    texture(0)
{
}

void Font::BuildTextGeometry(const String &text, TextGeometry &textGeom)
{
    uint len = text.length();
    if (len > MAX_TEXT_LENGTH)
    {
        LOG_WARNING("Max text length is %", MAX_TEXT_LENGTH);
        len = MAX_TEXT_LENGTH;
    }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    uint numChars = 0;

    for (uint i = 0; i < len; i++)
    {
        uint8 chr = text[i];
        Char &c = chars[chr];

        if (c.w == 0) continue;

        float x1 = x + c.xoffs;
        float y1 = y + c.yoffs;
        float x2 = x1 + c.w;
        float y2 = y1 + c.h;
        float u1 = float(c.x) / texW;
        float v1 = float(c.y) / texH;
        float u2 = float(c.x + c.w) / texW;
        float v2 = float(c.y + c.h) / texH;

        uint v = numChars * 4;

        vertices[v + 0].position = Vector3(x1, y1, z);
        vertices[v + 0].texcoord = Vector2(u1, v1);
        vertices[v + 1].position = Vector3(x2, y1, z);
        vertices[v + 1].texcoord = Vector2(u2, v1);
        vertices[v + 2].position = Vector3(x2, y2, z);
        vertices[v + 2].texcoord = Vector2(u2, v2);
        vertices[v + 3].position = Vector3(x1, y2, z);
        vertices[v + 3].texcoord = Vector2(u1, v2);

        x += c.advance;

        numChars++;
    }

    float *offs = 0;

    textGeom.fontTexture = texture;
    if (!textGeom.vertexBuffer)
        textGeom.vertexBuffer.reset(new VertexBuffer());
    textGeom.vertexBuffer->SetData(numChars * 4 * sizeof(Vert), vertices.data());
    textGeom.vertexBuffer->SetAttribute(VA_POSITION, sizeof(Vert), offs + 0);
    textGeom.vertexBuffer->SetAttribute(VA_TEXCOORD, sizeof(Vert), offs + 3);
    textGeom.indexBuffer = indexBuffer;
    textGeom.indexCount = numChars * 6;
}
