
#include "SceneObject.h"
#include "../Render/Model.h"
#include "../Render/Shader.h"

SceneObject::SceneObject() :
    model(0)
{
}

void SceneObject::SetModel(Model *mdl)
{
    model = mdl;
}

void SceneObject::Render(Shader *shader)
{
    if (model)
    {
        shader->SetModelMatrix(GetWorldTransform());
        model->Render();
    }
}
