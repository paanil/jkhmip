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

#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

#include "../Types.h"

/// Index buffer class.
///
class IndexBuffer
{
public:
    /// Gets a gl buffer resource.
    /// GL context must be created beforehand.
    IndexBuffer();
    /// Releases the gl buffer resource.
    ~IndexBuffer();

    /// Sets element array buffer (=index buffer) data.
    void SetData(uint dataSize, const void *data);

    /// Binds index buffer.
    void Bind();

    /// Draws triangles in range [firstIndex, firstIndex + indexCount).
    /// TODO: This should probably be somewhere else.
    void DrawTriangles(uint firstIndex, uint indexCount);

private:
    /// GL buffer id.
    uint buffer;
};

#endif // __INDEXBUFFER_H__
