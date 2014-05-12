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

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "../Types.h"

/// Texture minification filter modes.
enum TexFilterMin
{
    TF_MIN_NEAREST = 0,
    TF_MIN_LINEAR,
    TF_MIN_NEAREST_MIP_NEAREST,
    TF_MIN_LINEAR_MIP_NEAREST,
    TF_MIN_NEAREST_MIP_LINEAR,
    TF_MIN_LINEAR_MIP_LINEAR,
};

/// Texture magnification filter modes.
enum TexFilterMag
{
    TF_MAG_NEAREST = 0,
    TF_MAG_LINEAR
};

/// Texture wrap modes.
enum TexWrap
{
    TW_CLAMP = 0,
    TW_REPEAT,
    TW_MIRROR
};

enum TexFmt
{
    TexFmt_RED = 0,
    TexFmt_RG,
    TexFmt_RGB,
    TexFmt_RGBA,
    TexFmt_DEPTH
};

/// Texture class.
///
class Texture
{
public:
    /// Gets a gl texture resource.
    /// GL context must be created beforehand.
    Texture();
    /// Releases the gl texture resource.
    ~Texture();

    void CreateTex2D(int w, int h, TexFmt fmt);

//    void CreateTexCube(int w, int h, TexFmt fmt);

    /// Uploads the texture image to the GPU.
    void SetTexImage(int w, int h, int bpp, const void *image);

    /// Sets texture filtering modes.
    void SetFilterMode(TexFilterMin minFilter, TexFilterMag magFilter);
    /// Sets texture wrap modes.
    void SetWrapMode(TexWrap wrapS, TexWrap wrapT);

    /// Generates mipmaps.
    void GenMipmaps();

    /// Binds texture to the specified texture unit.
    void Bind(int textureUnit);

private:
    /// GL texture id.
    uint texture;
};

#endif // __TEXTURE_H__
