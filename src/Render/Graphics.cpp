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

#include "Graphics.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <GL/glew.h>

namespace Graphics
{

template <typename T>
class RenderState
{
public:
    virtual ~RenderState()
    {
    }

    void Set(T next)
    {
        this->next = next;
    }

protected:
    T current;
    T next;
};

class BlendState : public RenderState<BlendMode>
{
public:
    void Apply()
    {
        if (current != next)
        {
            switch (next)
            {
            case BM_NONE:
                glDisable(GL_BLEND);
                break;

            case BM_MIX:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;

            case BM_ADD:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                break;
            }
            current = next;
        }
    }
};

class TextureState : public RenderState<Texture *>
{
public:
    void SetUnit(int unit)
    {
        this->unit = unit;
    }

    void Apply()
    {
        if (current != next)
        {
            if (next != 0)
                next->Bind(unit);
            else
            {
                glActiveTexture(GL_TEXTURE0 + unit);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            current = next;
        }
    }

private:
    int unit;
};

class ShaderState : public RenderState<Shader *>
{
public:
    void Apply()
    {
        if (current != next)
        {
            if (next != 0)
            {
                next->Use();
                // TODO: Set uniforms.
            }
            else
                glUseProgram(0);
            current = next;
        }
    }
};

class VertexBufferState : public RenderState<VertexBuffer *>
{
public:
    void Apply()
    {
        if (current != next)
        {
            for (uint i = 0; i < VA_COUNT; i++)
                glDisableVertexAttribArray(i);
            if (next != 0)
                next->Bind();
            else
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            current = next;
        }
    }
};

class IndexBufferState : public RenderState<IndexBuffer *>
{
public:
    void Apply()
    {
        if (current != next)
        {
            if (next != 0)
                next->Bind();
            else
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            current = next;
        }
    }
};

void SetViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

void Clear(uint mask)
{
    static GLbitfield gl_masks[] =
    {
        0,
        GL_COLOR_BUFFER_BIT,
        GL_DEPTH_BUFFER_BIT,
        GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
    };

    glClear(gl_masks[mask]);
}

struct State
{
    BlendState blendMode;
    TextureState textures[8];
    ShaderState shader;
    VertexBufferState vbo;
    IndexBufferState ibo;
} state;

void ApplyState()
{
    state.blendMode.Apply();

    for (int i = 0; i < 8; i++)
        state.textures[i].Apply();

    state.shader.Apply();
    state.vbo.Apply();
    state.ibo.Apply();
}

void InitState()
{
    for (int i = 0; i < 8; i++)
        state.textures[i].SetUnit(i);

    ResetState();
    ApplyState();
}

void ResetState()
{
    state.blendMode.Set(BM_NONE);
    for (int i = 0; i < 8; i++)
        state.textures[i].Set(0);
    state.shader.Set(0);
    state.vbo.Set(0);
    state.ibo.Set(0);
}

void SetBlendMode(BlendMode mode)
{
    state.blendMode.Set(mode);
}

void SetTexture(Texture *tex, int unit)
{
    state.textures[unit].Set(tex);
}

void SetShader(Shader *shader)
{
    state.shader.Set(shader);
    state.shader.Apply(); // TODO: Remove.
}

void SetVertexBuffer(VertexBuffer *vbo)
{
    state.vbo.Set(vbo);
}

void SetIndexBuffer(IndexBuffer *ibo)
{
    state.ibo.Set(ibo);
}

void DrawTriangles(uint firstIndex, uint indexCount)
{
    ApplyState();

    uint *offs = 0; offs += firstIndex;
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, offs);
}

} // Graphics
