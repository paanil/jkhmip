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

#ifndef __SHADERCACHE_H__
#define __SHADERCACHE_H__

#include "ResourceCache.h"
#include "../Render/Shader.h"

/// Cache for shaders.
///
class ShaderCache : public ResourceCache<Shader>
{
protected:
    /// Loads a shader from given file.
    Shader *Load(const String &filePath);

private:
    /// Loads vertex and fragment shader sources from single file.
    /// The file must contain line ":vert" stating where begins the vertex shader
    /// and line ":frag" stating where begins the fragment shader.
    bool LoadSourceFile(const String &file, String &vertSrc, String &fragSrc);
};

#endif // __SHADERCACHE_H__
