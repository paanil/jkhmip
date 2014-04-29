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

#include "SceneCamera.h"
#include "SceneObject.h"

#include <vector>
#include <memory>

class Model;
class Shader;

/// Scene class that holds the scene nodes.
///
class Scene
{
    typedef std::unique_ptr<SceneNode> SceneNodePtr;
    typedef std::vector<SceneNodePtr> NodeList;
//    typedef std::vector<SceneCamera *> CameraList;
    typedef std::vector<SceneObject *> ObjectList;

public:
    /// Creates a camera node.
    SceneCamera *CreateCamera();
    /// Creates a renderable scene object node.
    SceneObject *CreateObject();

    /// Renders the scene with given shader.
    void Render(SceneCamera *camera, Shader *shader);

private:
    /// Adds a scene node to the node list.
    void AddNode(SceneNode *node);

private:
    NodeList nodes;
//    CameraList cameras;
    ObjectList objects;
};

#endif // __SCENE_H__
