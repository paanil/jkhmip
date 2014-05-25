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

void ResourceManager::LoadScene(Scene::Scene &scene, Logic &logic, const String &file)
{
    sceneLoader.Load(scene, logic, file);
}
