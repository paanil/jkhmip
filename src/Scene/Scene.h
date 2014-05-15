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

#ifndef __SCENE_H__
#define __SCENE_H__

#include "Camera.h"
#include "Object.h"
#include "Light.h"

#include <memory>

class Frustum;

namespace Scene
{

    /// Scene class that holds the scene nodes.
    ///
    class Scene
    {
        typedef std::unique_ptr<Node> NodePtr;
        typedef std::vector<NodePtr> NodeList;

    public:
        /// Creates a dummy node.
        Node *CreateDummy();
        /// Creates a camera node.
        Camera *CreateCamera();
        /// Creates a renderable scene object node.
        Object *CreateObject();

        Light *CreateLight();

        void FrustumCull(const Frustum &frustum, ObjectList &objects, LightList *lights = 0);

    private:
        /// Adds a scene node to the node list.
        void AddNode(Node *node);

    private:
        NodeList nodes;
        ObjectList objects;
        LightList lights;
    };

} // Scene

#endif // __SCENE_H__
