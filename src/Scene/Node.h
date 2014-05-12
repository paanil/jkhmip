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

#ifndef __NODE_H__
#define __NODE_H__

#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"
#include "../Math/AABB.h"

#include <vector>

namespace Scene
{

    /// Base class for all scene nodes.
    ///
    class Node
    {
    public:
        /// Sets parent to 0.
        Node();
        /// Virtual destructor.
        virtual ~Node();

        /// Removes this from old parent and adds to the new parent.
        void SetParent(Node *node);
        /// Returns parent node.
        Node *GetParent() const;

        /// Adds a child node.
        void AddChild(Node *node);
        /// Removes a child node.
        void RemoveChild(Node *node);

        /// Sets local position.
        void SetPosition(const Vector3 &pos);
        /// Gets local position.
        Vector3 GetPosition() const;

        /// Sets local rotation.
        void SetRotation(const Matrix3 &rot);
        /// Gets local rotation.
        const Matrix3 &GetRotation() const;

        /// Sets local scale.
        /// Assumes mat[i] is i'th column.
        void SetScale(const Vector3 &scale);
        /// Gets local scale.
        Vector3 GetScale()const;

        /// Gets the local rotation basis vectors.
        void GetBasisVectors(Vector3 &right, Vector3 &up, Vector3 &look) const;

        /// Gets local transform matrix.
        Matrix4 GetLocalTransform() const;
        /// Gets world transform matrix.
        const Matrix4 &GetWorldTransform();
        /// Gets the inverse world transform matrix.
        Matrix4 GetInverseWorldTransform();

        /// Gets axis aligned bounding box in world space.
        virtual const AABB &GetWorldAABB() const;

    private:
        /// Sets world transform dirty flag.
        /// Dirties children as well.
        void SetDirty();

    private:
        typedef std::vector<Node *> NodeList;

        Node *parent;
        NodeList children;

        Vector3 position;
        Matrix3 rotation;
        Vector3 scale;

        Matrix4 worldTransform;
        bool worldDirty;

    protected:
        AABB worldAABB;
        bool aabbDirty;
    };

} // Scene

#endif // __NODE_H__
