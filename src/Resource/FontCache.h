
#ifndef __FONTCACHE_H__
#define __FONTCACHE_H__

#include "ResourceCache.h"
#include "Font.h"

class TextureCache;

class FontCache : public ResourceCache<Font>
{
public:
    FontCache();
    void SetTextureCache(TextureCache &textureCache);

protected:
    Font *Load(const String &filePath);

private:
    TextureCache *textureCache;
};

#endif // __FONTCACHE_H__
