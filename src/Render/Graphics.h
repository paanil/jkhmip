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

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "../Types.h"

enum
{
    CLEAR_COLOR = 1,
    CLEAR_DEPTH = 2,
    CLEAR_COLOR_AND_DEPTH = CLEAR_COLOR | CLEAR_DEPTH
};

enum BlendMode
{
    BM_NONE,
    BM_MIX,
    BM_ADD
};

class Texture;
class Shader;
class VertexBuffer;
class IndexBuffer;

namespace Graphics
{
    void SetViewport(int x, int y, int w, int h);
    void Clear(uint mask);

    void InitState();
    void ResetState();
    void ApplyState();

    void SetBlendMode(BlendMode mode);
    void SetTexture(Texture *tex, int unit);
    void SetShader(Shader *shader);
    void SetVertexBuffer(VertexBuffer *vbo);
    void SetIndexBuffer(IndexBuffer *ibo);

    /// Draws triangles in range [firstIndex, firstIndex + indexCount).
    void DrawTriangles(uint firstIndex, uint indexCount);
}

#endif // __GRAPHICS_H__
