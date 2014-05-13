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

#include "Node.h"
#include "../Logger.h"

#include <algorithm>

namespace Scene
{

Node::Node() :
    parent(0),
    position(0.0f, 0.0f, 0.0f),
    rotation(Matrix3::Identity()),
    scale(1.0f, 1.0f, 1.0f),
    worldTransform(Matrix4::Identity()),
    worldDirty(false),
    aabbDirty(false)
{
}

Node::~Node()
{
}

void Node::SetParent(Node *node)
{
    if (parent)
        parent->RemoveChild(this);

    parent = node;

    if (parent)
        parent->AddChild(this);

    SetDirty();
}

Node *Node::GetParent() const
{
    return parent;
}

void Node::AddChild(Node *node)
{
    children.push_back(node);
}

void Node::RemoveChild(Node *node)
{
    auto it = std::find(children.begin(), children.end(), node);
    if (it == children.end())
    {
        LOG_WARNING("Scene::Node: Trying to remove child not in children.");
        return;
    }
    children.erase(it);
}

void Node::SetPosition(const Vector3 &pos)
{
    position = pos;
    SetDirty();
}

Vector3 Node::GetPosition() const
{
    return position;
}

void Node::SetRotation(const Matrix3 &rot)
{
    rotation = rot;
    SetDirty();
}

const Matrix3 &Node::GetRotation() const
{
    return rotation;
}

void Node::SetScale(const Vector3 &scale)
{
    this->scale = scale;
    SetDirty();
}

Vector3 Node::GetScale() const
{
    return scale;
}

void Node::GetBasisVectors(Vector3 &right, Vector3 &up, Vector3 &look) const
{
    right = Vector3(rotation.m11, rotation.m21, rotation.m31);
    up    = Vector3(rotation.m12, rotation.m22, rotation.m32);
    look  = Vector3(rotation.m13, rotation.m23, rotation.m33);
}

Matrix4 Node::GetLocalTransform() const
{
    Matrix4 M;
    M.m14 = position.x;
    M.m24 = position.y;
    M.m34 = position.z;
    M.m44 = 1.0f;
    for (int i = 0; i < 3; i++)
    {
        M.mat[0][i] = rotation.mat[0][i] * scale.x;
        M.mat[1][i] = rotation.mat[1][i] * scale.y;
        M.mat[2][i] = rotation.mat[2][i] * scale.z;
        M.mat[i][3] = 0.0f;
    }
    return M;
}

const Matrix4 &Node::GetWorldTransform()
{
    if (worldDirty)
    {
        if (parent)
            worldTransform = parent->GetWorldTransform() * GetLocalTransform();
        else
            worldTransform = GetLocalTransform();

        worldDirty = false;
    }

    return worldTransform;
}

Matrix4 Node::GetInverseWorldTransform()
{
    return GetWorldTransform().InverseTRS();
}

const AABB &Node::GetWorldAABB() const
{
    return worldAABB;
}

void Node::SetDirty()
{
    if (!worldDirty)
    {
        worldDirty = true;
        aabbDirty = true;
        for (Node *n : children)
        {
            n->SetDirty();
        }
    }
}

} // Scene
