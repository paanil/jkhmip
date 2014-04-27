
#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__

#include "SceneNode.h"

class Model;
class Shader;

class SceneObject : public SceneNode
{
public:
    SceneObject();

    void SetModel(Model *mdl);

    void Render(Shader *shader);

private:
    Model *model;
};

#endif // __SCENEOBJECT_H__
