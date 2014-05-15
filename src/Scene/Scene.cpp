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
#include "../Render/RenderCommand.h"
#include "../Math/Frustum.h"

namespace Scene
{

Node *Scene::CreateDummy()
{
    Node *node = new Node();
    AddNode(node);
    return node;
}

Camera *Scene::CreateCamera()
{
    Camera *camera = new Camera();
    AddNode(camera);
    return camera;
}

Object *Scene::CreateObject()
{
    Object *object = new Object();
    objects.push_back(object);
    AddNode(object);
    return object;
}

Light *Scene::CreateLight()
{
    Light *light = new Light();
    lights.push_back(light);
    AddNode(light);
    return light;
}

void Scene::FrustumCull(const Frustum &frustum, ObjectList &objects, LightList *lights)
{
    for (Object *object : this->objects)
    {
        if ( frustum.TestAABB(object->GetWorldAABB()) )
            objects.push_back(object);
    }

    if (lights == 0)
        return;

    for (Light *light : this->lights)
    {
        if (light->GetRadius() <= 0.0f)
            lights->push_back(light);
    }

    for (Light *light : this->lights)
    {
        Vector4 pos = light->GetLightPos();
        if ( pos.w > 0.0f && frustum.TestSphere(pos) )
            lights->push_back(light);
    }
}

void Scene::AddNode(Node *node)
{
    nodes.push_back(NodePtr(node));
}

} // Scene
