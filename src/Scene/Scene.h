
#ifndef __SCENE_H__
#define __SCENE_H__

#include "SceneCamera.h"
#include "SceneObject.h"

#include <vector>
#include <memory>

class Model;
class Shader;

class Scene
{
    typedef std::unique_ptr<SceneNode> SceneNodePtr;
    typedef std::vector<SceneNodePtr> NodeList;
    typedef std::vector<SceneObject *> ObjectList;

public:
    Scene();

    SceneCamera *GetCamera();
    SceneObject *CreateObject();

    void Render(Shader *shader);

private:
    void AddNode(SceneNode *node);

private:
    NodeList nodes;
    SceneCamera *camera;
    ObjectList objects;
};

#endif // __SCENE_H__
