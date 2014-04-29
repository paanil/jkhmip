
#ifndef __MATERIALCACHE_H__
#define __MATERIALCACHE_H__

#include "ResourceCache.h"
#include "../Render/Material.h"

class ShaderCache;
class TextureCache;

class MaterialCache : public ResourceCache<Material>
{
public:
    MaterialCache();

    void SetShaderCache(ShaderCache &shaderCache);
    void SetTextureCache(TextureCache &textureCache);

protected:
    Material *Load(const String &filePath);

    Material *LoadMaterial(const String &file);

private:
    ShaderCache *shaderCache;
    TextureCache *textureCache;
};

#endif // __MATERIALCACHE_H__
