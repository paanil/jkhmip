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

#include "MaterialCache.h"
#include "ShaderCache.h"
#include "TextureCache.h"
#include "../Logger.h"

#include <fstream>

MaterialCache::MaterialCache() :
    shaderCache(0),
    textureCache(0)
{
}

void MaterialCache::SetShaderCache(ShaderCache &shaderCache)
{
    this->shaderCache = &shaderCache;
}

void MaterialCache::SetTextureCache(TextureCache &textureCache)
{
    this->textureCache = &textureCache;
}

Material *MaterialCache::Load(const String &filePath)
{
    Material *material = LoadMaterial(filePath);

    if (material == 0)
    {
        LOG_INFO("Using debug material.");
        material = new Material();
        material->SetShader(shaderCache->Get("debug"));
        material->SetTexture(textureCache->Get("debug"));
    }

    return material;
}

Material *MaterialCache::LoadMaterial(const String &file)
{
    LOG_INFO("Loading material '%'...", file);

    std::ifstream f(file.c_str());

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        return 0;
    }

    String shader;

    if (!std::getline(f, shader))
    {
        LOG_ERROR("Material needs a shader.");
        return 0;
    }

    String texture;

    if (!std::getline(f, texture))
    {
        LOG_ERROR("Material needs a texture.");
        return 0;
    }

    Material *material = new Material();

    material->SetShader(shaderCache->Get(shader));
    material->SetTexture(textureCache->Get(texture));

    return material;
}
