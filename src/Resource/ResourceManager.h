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

    void LoadScene(Scene::Scene &scene, LogicSystem &logic, const String &file);

private:
    TextureCache    textureCache;
    ShaderCache     shaderCache;
    MaterialCache   materialCache;
    ModelCache      modelCache;
    FontCache       fontCache;
    SceneLoader     sceneLoader;
};

#endif // __RESOURCEMANAGER_H__
