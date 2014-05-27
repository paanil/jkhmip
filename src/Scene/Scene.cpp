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

Scene::Scene() :
    sky(0)
{
}

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

Light *Scene::CreateDirLight()
{
    Light *light = new Light();
    light->SetType(Vector3(1.0f, 0.0f, 0.0f));
    light->CreateShadowMap(4096);
    dirLights.push_back(LightPtr(light));
    return light;
}

Light *Scene::CreateSpotLight()
{
    Light *light = new Light();
    light->SetType(Vector3(0.0f, 1.0f, 0.0f));
    light->CreateShadowMap(512);
    spotLights.push_back(LightPtr(light));
    return light;
}

Light *Scene::CreatePointLight()
{
    Light *light = new Light();
    light->SetType(Vector3(0.0f, 0.0f, 1.0f));
    pointLights.push_back(LightPtr(light));
    return light;
}

Object *Scene::CreateSky()
{
    sky = new Object();
    AddNode(sky);
    return sky;
}

AABB Scene::GetBoundingBox() const
{
    AABB bounds = AABB::Degenerate();
    for (Object *object : this->objects)
        bounds.Update(object->GetWorldAABB());
    return bounds;
}

void Scene::FrustumCull(const Frustum &frustum, ObjectList &objects, LightList &lights)
{
    for (Object *object : this->objects)
    {
        if ( frustum.TestAABB(object->GetWorldAABB()) )
            objects.push_back(object);
    }

    for (LightPtr &light : dirLights)
        lights.push_back(light.get());

    for (LightPtr &light : spotLights)
    {
        if ( frustum.TestAABB(light->GetLightAABB()) )
            lights.push_back(light.get());
    }

    for (LightPtr &light : pointLights)
    {
        if ( frustum.TestSphere(light->GetPos(), light->GetRadius()) )
            lights.push_back(light.get());
    }
}

void Scene::FrustumCullForShadowMap(const Frustum &frustum, ObjectList &objects)
{
    for (Object *object : this->objects)
    {
        if ( object->GetCastShadows() && frustum.TestAABB(object->GetWorldAABB()) )
            objects.push_back(object);
    }
}

Object *Scene::GetSky() const
{
    return sky;
}

void Scene::AddNode(Node *node)
{
    nodes.push_back(NodePtr(node));
}

} // Scene
