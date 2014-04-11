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

#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include "../Types.h"

enum
{
    VA_POSITION = 0,
    VA_TEXCOORD,
    VA_NORMAL,
    VA_COUNT
};

extern const char *VA_NAMES[];

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void SetData(uint dataSize, const void *data);
    void SetAttribute(uint index, uint stride, const void *pointer);

    void Bind();

private:
    void BindAttribute(uint index);

private:
    uint buffer;

    struct Attribute
    {
        int         size;
        uint        type;
        uint        normalized;
        int         stride;
        const void *pointer;
    };

    Attribute attributes[VA_COUNT];
};

#endif // __VERTEXBUFFER_H__
