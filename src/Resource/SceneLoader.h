
#ifndef __SCENELOADER_H__
#define __SCENELOADER_H__

#include "../Types.h"

class Scene;
class ModelCache;

class SceneLoader
{
public:
    SceneLoader();

    void SetDirectory(const String &dir);

    void SetModelCache(ModelCache &modelCache);

    bool LoadScene(Scene &scene, const String &file);

private:
    String directory;

    ModelCache *modelCache;
};

#endif // __SCENELOADER_H__
