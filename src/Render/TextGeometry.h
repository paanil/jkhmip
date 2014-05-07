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

#ifndef __TEXTGEOMETRY_H__
#define __TEXTGEOMETRY_H__

#include "VertexBuffer.h"

#include <memory>

class Texture;
class IndexBuffer;

class TextGeometry
{
public:
    Texture *GetFontTexture() const;
    VertexBuffer *GetVertexBuffer() const;
    IndexBuffer *GetIndexBuffer() const;
    uint GetIndexCount() const;

private:
    Texture *fontTexture;
    VertexBufferPtr vertexBuffer;
    IndexBuffer *indexBuffer;
    uint indexCount;

    friend class Font;
};

#endif // __TEXTGEOMETRY_H__
