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
#include "../Resource/Image.h"
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

void Texture::SetTexImage(const Image *image)
{
    GLint format = 0;
    switch (image->GetBytesPerPixel())
    {
    case 1:
        format = GL_RED;
        break;

    case 3:
        format = GL_RGB;
        break;

    case 4:
        format = GL_RGBA;
        break;

    default:
        LOG_ERROR("Texture: Only gray scale, RGB and RGBA images are supported.");
        return;
    }

    Bind(0);
    glTexImage2D(GL_TEXTURE_2D, 0, format,
                 image->GetWidth(),
                 image->GetHeight(),
                 0, format, GL_UNSIGNED_BYTE,
                 image->GetData());

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterModes[minFilter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterModes[magFilter]);
}

void Texture::SetWrapMode(TexWrap wrapS, TexWrap wrapT)
{
    static const GLenum wrapModes[] =
    {
        GL_CLAMP, GL_REPEAT, GL_MIRRORED_REPEAT
    };

    Bind(0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModes[wrapS]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModes[wrapT]);
}

void Texture::GenMipmaps()
{
    Bind(0);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Bind(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture);
}
