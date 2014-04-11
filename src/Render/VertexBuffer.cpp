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

#include "VertexBuffer.h"
#include "../Logger.h"

#include <GL/glew.h>

const char *VA_NAMES[] =
{
    "Position",
    "TexCoord",
    "Normal"
};

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &buffer);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &buffer);
}

void VertexBuffer::SetData(uint dataSize, const void *data)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    for (int i = 0; i < VA_COUNT; i++)
    {
        attributes[i].size = 0;
    }
}

void VertexBuffer::SetAttribute(uint index, uint stride, const void *pointer)
{
    switch (index)
    {
    case VA_POSITION:
        attributes[index].size = 3;
        attributes[index].type = GL_FLOAT;
        attributes[index].normalized = GL_FALSE;
        break;

    case VA_TEXCOORD:
        attributes[index].size = 2;
        attributes[index].type = GL_FLOAT;
        attributes[index].normalized = GL_FALSE;
        break;

    case VA_NORMAL:
        attributes[index].size = 3;
        attributes[index].type = GL_FLOAT;
        attributes[index].normalized = GL_FALSE;
        break;

    default:
        LOG_ERROR("Invalid vertex attribute array index.");
        return;
    }

    attributes[index].stride = stride;
    attributes[index].pointer = pointer;
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    for (int i = 0; i < VA_COUNT; i++)
    {
        if (attributes[i].size > 0)
        {
            BindAttribute(i);
        }
    }
}

void VertexBuffer::BindAttribute(uint index)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index,
                          attributes[index].size,
                          attributes[index].type,
                          attributes[index].normalized,
                          attributes[index].stride,
                          attributes[index].pointer);
}
