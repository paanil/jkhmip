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

Texture *TextureCache::Load(const String &filePath)
{
    static const uint8 debugTexImage[] = { 128, 128, 255 };

    int w = 1, h = 1, bpp = 3;
    const void *data = debugTexImage;

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
    }

    Texture *texture = new Texture();
    texture->SetTexImage(w, h, bpp, data);
    return texture;
}
