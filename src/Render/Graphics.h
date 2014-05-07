
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

    void SetBlendMode(BlendMode mode);
    void SetTexture(Texture *tex, int unit);
    void SetShader(Shader *shader);
    void SetVertexBuffer(VertexBuffer *vbo);
    void SetIndexBuffer(IndexBuffer *ibo);

    void DrawTriangles(uint firstIndex, uint indexCount);
}

#endif // __GRAPHICS_H__
