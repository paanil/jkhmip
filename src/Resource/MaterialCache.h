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
