
#include "SceneNode.h"
#include "../Logger.h"

#include <algorithm>

SceneNode::SceneNode()
{
    parent = 0;
    localTransform = Matrix4::Identity();
    worldTransform = Matrix4::Identity();
    worldDirty = false;
}

SceneNode::~SceneNode()
{
}

void SceneNode::SetParent(SceneNode *node)
{
    if (parent)
        parent->RemoveChild(this);

    parent = node;

    if (parent)
        parent->AddChild(this);
}

SceneNode *SceneNode::GetParent() const
{
    return parent;
}

void SceneNode::AddChild(SceneNode *node)
{
    children.push_back(node);
}

void SceneNode::RemoveChild(SceneNode *node)
{
    auto it = std::find(children.begin(), children.end(), node);
    if (it == children.end())
    {
        LOG_WARNING("SceneNode: Trying to remove child not in children.");
        return;
    }
    children.erase(it);
}

void SceneNode::SetPosition(const Vector3 &pos)
{
    localTransform.m14 = pos.x;
    localTransform.m24 = pos.y;
    localTransform.m34 = pos.z;

    SetDirty();
}

Vector3 SceneNode::GetPosition() const
{
    const Matrix4 &tm = localTransform;
    return Vector3(tm.m14, tm.m24, tm.m34);
}

void SceneNode::SetRotation(const Matrix3 &rot)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            localTransform.mat[i][j] = rot.mat[i][j];
    }

    SetDirty();
}

Matrix3 SceneNode::GetRotation() const
{
    Matrix3 rot;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            rot.mat[i][j] = localTransform.mat[i][j];
    }
    return rot;
}

void SceneNode::GetBasisVectors(Vector3 &right, Vector3 &up, Vector3 &look) const
{
    const Matrix4 &tm = localTransform;
    right = Vector3(tm.m11, tm.m21, tm.m31);
    up    = Vector3(tm.m12, tm.m22, tm.m32);
    look  = Vector3(tm.m13, tm.m23, tm.m33);
}

const Matrix4 &SceneNode::GetLocalTransform() const
{
    return localTransform;
}

const Matrix4 &SceneNode::GetWorldTransform()
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

Matrix4 SceneNode::GetInverseWorldTransform()
{
    return GetWorldTransform().InverseTR();
}

void SceneNode::SetDirty()
{
    if (!worldDirty)
    {
        worldDirty = true;
        for (SceneNode *n : children)
        {
            n->SetDirty();
        }
    }
}
