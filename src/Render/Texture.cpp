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

#include "Texture.h"
#include "../Logger.h"

#include <GL/glew.h>

Texture::Texture()
{
    glGenTextures(1, &texture);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

void Texture::CreateTex2D(int w, int h, TexFmt fmt)
{
    static const GLint internal_formats[] =
    {
        GL_RED, GL_RG,  GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT24
    };
    static const GLenum formats[] =
    {
        GL_RED, GL_RG,  GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT
    };
    static const GLenum types[] =
    {
        GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE, GL_UNSIGNED_BYTE, GL_FLOAT
    };

    target = GL_TEXTURE_2D;

    Bind(0);
    glTexImage2D(target, 0, internal_formats[fmt], w, h, 0, formats[fmt], types[fmt], 0);

    SetFilterMode(TF_MIN_NEAREST, TF_MAG_NEAREST);
    SetWrapMode(TW_CLAMP, TW_CLAMP);

    if (fmt == TexFmt_DEPTH)
    {
        SetFilterMode(TF_MIN_LINEAR, TF_MAG_LINEAR);
        glTexParameteri(target, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
        glTexParameteri(target, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    }
}

void SetTexImage(GLenum target, int w, int h, int bpp, const void *image)
{
    GLint format = 0;
    switch (bpp)
    {
    case 1: format = GL_RED; break;
    case 3: format = GL_RGB; break;
    case 4: format = GL_RGBA;break;

    default:
        LOG_ERROR("Texture: Only gray scale, RGB and RGBA images are supported.");
        return;
    }

    glTexImage2D(target, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
}

void Texture::SetTexImage2D(int w, int h, int bpp, const void *image)
{
    target = GL_TEXTURE_2D;
    Bind(0);
    SetTexImage(target, w, h, bpp, image);
    SetFilterMode(TF_MIN_NEAREST, TF_MAG_NEAREST);
    SetWrapMode(TW_CLAMP, TW_CLAMP);
}

void Texture::SetTexImageCube(int side, int w, int h, int bpp, const void *image)
{
    target = GL_TEXTURE_CUBE_MAP;
    Bind(0);
    SetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, w, h, bpp, image);
    SetFilterMode(TF_MIN_NEAREST, TF_MAG_NEAREST);
    SetWrapMode(TW_CLAMP, TW_CLAMP);
}

void Texture::SetFilterMode(TexFilterMin minFilter, TexFilterMag magFilter)
{
    static const GLenum filterModes[] =
    {
        GL_NEAREST, GL_LINEAR,
        GL_NEAREST_MIPMAP_NEAREST,
        GL_LINEAR_MIPMAP_NEAREST,
        GL_NEAREST_MIPMAP_LINEAR,
        GL_LINEAR_MIPMAP_LINEAR
    };

    Bind(0);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filterModes[minFilter]);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filterModes[magFilter]);
}

void Texture::SetWrapMode(TexWrap wrapS, TexWrap wrapT)
{
    static const GLenum wrapModes[] =
    {
        GL_CLAMP_TO_EDGE, GL_REPEAT, GL_MIRRORED_REPEAT
    };

    Bind(0);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapModes[wrapS]);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapModes[wrapT]);
}

void Texture::GenMipmaps()
{
    Bind(0);
    glGenerateMipmap(target);
    if (GLEW_EXT_texture_filter_anisotropic)
    {
        GLfloat max_anisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
        glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
    }
}

void Texture::Bind(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(target, texture);
}
