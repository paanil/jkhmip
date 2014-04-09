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

typedef std::unique_ptr<Image> ImagePtr;

Texture *TextureCache::Get(const String &file)
{
    auto it = resources.find(file);
    if (it != resources.end())
    {
        return it->second.get();
    }

    ImagePtr image(LoadImage(direcotry + file));

    if (!image)
    {
        LOG_INFO("Using debug texture.");
        image.reset(MakeImage(16, 16, 3, 128, 128, 255, 0));
    }

    Texture *texture = new Texture();
    texture->SetTexImage(image->GetWidth(),
                         image->GetHeight(),
                         image->GetBytesPerPixel(),
                         image->GetData());

    resources[file] = ResourcePtr(texture);
    return texture;
}
