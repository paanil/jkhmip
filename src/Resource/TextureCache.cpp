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

#include "TextureCache.h"
#include "Image.h"
#include "../Logger.h"
#include "../Str.h"

#include <fstream>

const uint8 debugTexImage[] = { 128, 128, 255 };

Texture *LoadTexture2D(const String &filePath);
Texture *LoadTextureCube(const String &filePath, const String &path);

Texture *TextureCache::Load(const String &filePath)
{
    LOG_INFO("Loading texture '%'...", filePath);

    size_t pos = filePath.find_last_of('.');

    if (pos != String::npos)
    {
        String ext = filePath.substr(pos + 1);

        if (StrIEquals(ext, "tga"))
            return LoadTexture2D(filePath);
        else if (StrIEquals(ext, "cube"))
            return LoadTextureCube(filePath, GetDirectory());
    }

    LOG_ERROR("Unknown image format.");
    LOG_INFO("Using debug texture.");

    int w = 1, h = 1, bpp = 3;
    const void *data = debugTexImage;
    Texture *texture = new Texture();
    texture->SetTexImage2D(w, h, bpp, data);
    return texture;
}

Texture *LoadTexture2D(const String &filePath)
{
    int w, h, bpp;
    const void *data;
    Image image;

    if (image.Load(filePath))
    {
        w = image.GetWidth();
        h = image.GetHeight();
        bpp = image.GetBytesPerPixel();
        data = image.GetData();
    }
    else
    {
        LOG_INFO("Using debug texture.");
        w = h = 1; bpp = 3;
        data = debugTexImage;
    }

    Texture *texture = new Texture();
    texture->SetTexImage2D(w, h, bpp, data);
    return texture;
}

Texture *LoadTextureCube(const String &filePath, const String &path)
{
    std::ifstream f(filePath.c_str());

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        LOG_ERROR("Using debug cube texture.");

        Texture *texture = new Texture();
        for (int i = 0; i < 6; i++)
            texture->SetTexImageCube(i, 1, 1, 3, debugTexImage);
        return texture;
    }

    Texture *texture = new Texture();

    for (int i = 0; i < 6; i++)
    {
        int w, h, bpp;
        const void *data;
        String file;
        Image image;

        if (std::getline(f, file))
        {
            file = path + file;
            LOG_INFO("Loading image '%'...", file);

            if (image.Load(file))
            {
                w = image.GetWidth();
                h = image.GetHeight();
                bpp = image.GetBytesPerPixel();
                data = image.GetData();
            }
            else
            {
                LOG_INFO("Using debug image.");
                w = h = 1; bpp = 3;
                data = debugTexImage;
            }
        }
        else
        {
            LOG_INFO("Cube side % not defined.", i);
            LOG_INFO("Using debug image.");
            w = h = 1; bpp = 3;
            data = debugTexImage;
        }

        texture->SetTexImageCube(i, w, h, bpp, data);
    }

    f.close();

    return texture;
}
