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

/// Indices of supported vertex attributes.
enum
{
    VA_POSITION = 0,
    VA_TEXCOORD,
    VA_NORMAL,
    VA_COUNT
};

/// Vertex attribute names.
/// Used for binding shader attribute locations.
extern const char *VA_NAMES[];

/// Vertex buffer class.
///
class VertexBuffer
{
public:
    /// Gets a gl buffer resource.
    /// GL context must be created beforehand.
    VertexBuffer();
    /// Releases the gl buffer resource.
    ~VertexBuffer();

    /// Sets vertex buffer data and 'clears' attributes.
    void SetData(uint dataSize, const void *data);

    /// Sets vertex attribute info.
    /// Attribute size depends on the index, type is always float and normalized false.
    /// \param index The index of the attribute to set (VA_POSITION, VA_TEXCOORD, ...)
    /// \param stride The stride of the attribute
    /// \param pointer The pointer offset of the attribute
    void SetAttribute(uint index, uint stride, const void *pointer);

    /// Binds vertex buffer.
    void Bind();

private:
    /// Binds vertex attribute corresponding the index.
    void BindAttribute(uint index);

private:
    /// GL buffer id.
    uint buffer;

    /// Vertex attribute info.
    struct Attribute
    {
        int         size;
        uint        type;
        uint        normalized;
        int         stride;
        const void *pointer;
    };

    /// Array of vertex attributes.
    Attribute attributes[VA_COUNT];
};

#endif // __VERTEXBUFFER_H__
