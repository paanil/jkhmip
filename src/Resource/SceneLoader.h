
#ifndef __SCENELOADER_H__
#define __SCENELOADER_H__

#include "../Types.h"

namespace Scene
{
    class Scene;
}

class Logic;
class ModelCache;

class SceneLoader
{
public:
    SceneLoader();

    void SetDirectory(const String &dir);

    void SetModelCache(ModelCache &modelCache);

    bool Load(Scene::Scene &scene, Logic &logic, const String &file);

private:
    String directory;

    ModelCache *modelCache;
};

#endif // __SCENELOADER_H__
