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

#ifndef __RENDERCOMMANDLIST_H__
#define __RENDERCOMMANDLIST_H__

#include "RenderCommand.h"
#include "../Scene/Light.h"

#include <vector>

class RenderCommandList
{
    typedef std::vector<RenderCommand> CommandList;

public:
    void ResetLights();

    bool AddLight(Scene::Light *light);

    void SetModelMatrix(const Matrix4 &modelMatrix);
    void SetMaterial(Material *material);
    void SetVertexBuffer(VertexBuffer *vbo);
    void SetIndexBuffer(IndexBuffer *ibo);

    void AddRenderCommand(uint firstIndex, uint indexCount);

    size_t Size() const;
    void Clear();

    RenderCommand &operator[](int i);

    CommandList::iterator begin();
    CommandList::iterator end();

private:
    RenderCommand command;
    CommandList commands;
};

#endif // __RENDERCOMMANDLIST_H__
