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
    model(0)
{
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
        const AABB &aabb = model->GetAABB();

        worldAABB = AABB::Degenerate();

        worldAABB.Update(M * Vector3(aabb.min.x, aabb.min.y, aabb.min.z));
        worldAABB.Update(M * Vector3(aabb.min.x, aabb.min.y, aabb.max.z));
        worldAABB.Update(M * Vector3(aabb.min.x, aabb.max.y, aabb.min.z));
        worldAABB.Update(M * Vector3(aabb.min.x, aabb.max.y, aabb.max.z));
        worldAABB.Update(M * Vector3(aabb.max.x, aabb.min.y, aabb.min.z));
        worldAABB.Update(M * Vector3(aabb.max.x, aabb.min.y, aabb.max.z));
        worldAABB.Update(M * Vector3(aabb.max.x, aabb.max.y, aabb.min.z));
        worldAABB.Update(M * Vector3(aabb.max.x, aabb.max.y, aabb.max.z));

        aabbDirty = false;
    }

    return worldAABB;
}

void Object::GetRenderCommands(RenderCommandList &commands)
{
    commands.SetTransform(GetWorldTransform());
    model->GetRenderCommands(commands);
}

} // Scene
