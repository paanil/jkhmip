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

#ifndef __FONTCACHE_H__
#define __FONTCACHE_H__

#include "ResourceCache.h"
#include "Font.h"

class TextureCache;

/// Cache for fonts.
///
class FontCache : public ResourceCache<Font>
{
public:
    /// Sets textureCache to 0.
    FontCache();
    /// Takes a pointer to a texture cache for later use.
    void SetTextureCache(TextureCache &textureCache);

protected:
    /// Loads a font from given file.
    Font *Load(const String &filePath);

private:
    /// For loading font textures.
    TextureCache *textureCache;
};

#endif // __FONTCACHE_H__
