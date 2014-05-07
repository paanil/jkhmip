
#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "TextureCache.h"
#include "ShaderCache.h"
#include "MaterialCache.h"
#include "ModelCache.h"
#include "FontCache.h"
#include "SceneLoader.h"

class ResourceManager
{
public:
    void Init();

    Texture *   GetTexture(const String &file);
    Shader *    GetShader(const String &file);
    Material *  GetMaterial(const String &file);
    Model *     GetModel(const String &file);
    Font *      GetFont(const String &file);

    void LoadScene(Scene::Scene &scene, const String &file);

private:
    TextureCache    textureCache;
    ShaderCache     shaderCache;
    MaterialCache   materialCache;
    ModelCache      modelCache;
    FontCache       fontCache;
    SceneLoader     sceneLoader;
};

#endif // __RESOURCEMANAGER_H__
