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

#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"

#include <vector>

/// Base class for all scene nodes.
///
class SceneNode
{
public:
    /// Sets parent to 0.
    SceneNode();
    /// Virtual destructor.
    virtual ~SceneNode();

    /// Removes this from old parent and adds to the new parent.
    void SetParent(SceneNode *node);
    /// Returns parent node.
    SceneNode *GetParent() const;

    /// Adds a child node.
    void AddChild(SceneNode *node);
    /// Removes a child node.
    void RemoveChild(SceneNode *node);

    /// Sets local position.
    void SetPosition(const Vector3 &pos);
    /// Gets local position.
    Vector3 GetPosition() const;

    /// Sets local rotation.
    void SetRotation(const Matrix3 &rot);
    /// Gets local rotation.
    Matrix3 GetRotation() const;

    /// Sets local scale.
    /// Assumes mat[i] is i'th column.
    void SetScale(const Vector3 &scale);
    /// Gets local scale.
    Vector3 GetScale()const;

    /// Gets the local rotation basis vectors.
    void GetBasisVectors(Vector3 &right, Vector3 &up, Vector3 &look) const;

    /// Gets local transform matrix.
    const Matrix4 &GetLocalTransform() const;
    /// Gets world transform matrix.
    const Matrix4 &GetWorldTransform();
    /// Gets the inverse world transform matrix.
    Matrix4 GetInverseWorldTransform();

private:
    /// Sets world transform dirty flag.
    /// Dirties children as well.
    void SetDirty();

private:
    typedef std::vector<SceneNode *> NodeList;

    SceneNode *parent;
    NodeList children;

    Matrix4 localTransform;
    Matrix4 worldTransform;
    bool worldDirty;

    friend class SceneLoader;
};

#endif // __SCENENODE_H__
