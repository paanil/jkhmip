
#include "ResourceManager.h"
#include "../Conf.h"

void ResourceManager::Init()
{
    textureCache.SetDirectory(Config::getString("Texture_location"));
    shaderCache.SetDirectory(Config::getString("Shader_location"));

    materialCache.SetDirectory(Config::getString("Material_location"));
    materialCache.SetShaderCache(shaderCache);
    materialCache.SetTextureCache(textureCache);

    modelCache.SetDirectory(Config::getString("Model_location"));
    modelCache.SetMaterialCache(materialCache);

    fontCache.SetDirectory(Config::getString("Font_location"));
    fontCache.SetTextureCache(textureCache);
    fontCache.InitIndexBuffer();

    sceneLoader.SetDirectory(Config::getString("Scene_location"));
    sceneLoader.SetModelCache(modelCache);
}

Texture *ResourceManager::GetTexture(const String &file)
{
    return textureCache.Get(file);
}

Shader *ResourceManager::GetShader(const String &file)
{
    return shaderCache.Get(file);
}

Material *ResourceManager::GetMaterial(const String &file)
{
    return materialCache.Get(file);
}

Model *ResourceManager::GetModel(const String &file)
{
    return modelCache.Get(file);
}

Font *ResourceManager::GetFont(const String &file)
{
    return fontCache.Get(file);
}

void ResourceManager::LoadScene(Scene::Scene &scene, const String &file)
{
    sceneLoader.Load(scene, file);
}
