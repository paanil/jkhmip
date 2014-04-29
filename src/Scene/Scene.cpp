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

#include "Scene.h"
#include "../Render/Shader.h"

SceneCamera *Scene::CreateCamera()
{
    SceneCamera *camera = new SceneCamera();
//    cameras.push_back(camera);
    AddNode(camera);
    return camera;
}

SceneObject *Scene::CreateObject()
{
    SceneObject *object = new SceneObject();
    objects.push_back(object);
    AddNode(object);
    return object;
}

void Scene::Render(SceneCamera *camera, Shader *shader)
{
    shader->SetProjMatrix(camera->GetProjection());
    shader->SetViewMatrix(camera->GetInverseWorldTransform());

    for (SceneObject *object : objects)
    {
        object->Render(shader);
    }
}

void Scene::AddNode(SceneNode *node)
{
    nodes.push_back(SceneNodePtr(node));
}
