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

#include "Object.h"
#include "../Render/Model.h"
#include "../Render/RenderCommand.h"

namespace Scene
{

Object::Object() :
    model(0),
    worldAABB(AABB::Degenerate()),
    aabbDirty(false),
    castShadows(false)
{
}

void Object::SetCastShadows(bool castShadows)
{
    this->castShadows = castShadows;
}

bool Object::GetCastShadows() const
{
    return castShadows;
}

void Object::SetModel(Model *model)
{
    this->model = model;
    aabbDirty = true;
}

const AABB &Object::GetWorldAABB()
{
    if (aabbDirty)
    {
        const Matrix4 &M = GetWorldTransform();
        worldAABB.Update(model->GetAABB().Transform(M));

        aabbDirty = false;
    }

    return worldAABB;
}

void Object::GetRenderCommands(RenderCommandList &commands)
{
    commands.SetModelMatrix(GetWorldTransform());
    model->GetRenderCommands(commands);
}

void Object::OnDirty()
{
    aabbDirty = true;
}

} // Scene
