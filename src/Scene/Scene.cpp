
#include "Scene.h"
#include "../Render/Shader.h"

Scene::Scene()
{
    camera = new SceneCamera();
    AddNode(camera);
}

SceneCamera *Scene::GetCamera()
{
    return camera;
}

SceneObject *Scene::CreateObject()
{
    SceneObject *object = new SceneObject();
    objects.push_back(object);
    AddNode(object);
    return object;
}

void Scene::Render(Shader *shader)
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
