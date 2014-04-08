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

#ifndef __TEXTURECACHE_H__
#define __TEXTURECACHE_H__

#include "../Types.h"

#include <memory>
#include <map>

// Forward declare Texture.
class Texture;

/// TextureCache class caches textures so they won't be
/// loaded every time they are needed. If same texture is
/// needed frequently, the pointer should be kept for efficiency.
/// Note that the cache owns the texture. Don't try to delete it.
class TextureCache
{
    /// Useful typedefs.
    typedef std::unique_ptr<Texture> TexturePtr;
    typedef std::map<String, TexturePtr> TextureMap;

public:
    /// Initializes empty texDirectory string.
    TextureCache();

    /// Sets the texDirectory where the textures are expected
    /// to be found. The string needs to end with '/' -char.
    void SetDirectory(const String &dir);

    /// Gets a texture identified by the file name.
    /// The texture is loaded if it's not in the cache.
    /// The file name is expected to be relative to the texDirectory.
    Texture *Get(const String &file);

private:
    /// Directory where all textures are loaded from.
    String texDirecotry;
    /// Map containing the cached textures.
    TextureMap textures;
};

#endif // __TEXTURECACHE_H__
