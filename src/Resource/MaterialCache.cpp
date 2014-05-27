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

    String line;

    if (!std::getline(f, line))
    {
        LOG_ERROR("Material needs a shader.");
        return 0;
    }

    Material *material = new Material();
    material->SetShader(shaderCache->Get(line));

    if (std::getline(f, line))
    {
        if (line == "double_sided")
            material->SetDoubleSided(true);
    }

    for (int i = 0; i < MAX_MATERIAL_TEXTURES; i++)
    {
        if (!std::getline(f, line)) break;
        Texture *tex = textureCache->Get(line);
        material->SetTexture(i, tex);
        tex->SetFilterMode(TF_MIN_LINEAR_MIP_LINEAR, TF_MAG_LINEAR);
        tex->SetWrapMode(TW_REPEAT, TW_REPEAT);
        tex->GenMipmaps();
    }

    return material;
}
