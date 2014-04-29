
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
