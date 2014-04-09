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

#include "Image.h"
#include "../Logger.h"

#include <fstream>
#include <cstring>
#include <cctype>

/* Image class */

Image::Image(int w, int h, int bpp, char *data) :
    w(w), h(h), bpp(bpp), data(data)
{
}

Image::~Image()
{
    delete[] data;
}

int Image::GetWidth() const
{
    return w;
}

int Image::GetHeight() const
{
    return h;
}

int Image::GetBytesPerPixel() const
{
    return bpp;
}

const char *Image::GetData() const
{
    return data;
}

/* Free functions */

Image *LoadTGA(const String &file)
{
    std::ifstream f(file.c_str(), std::ifstream::binary);

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.", file);
        return 0;
    }

    // read header
    unsigned char header[18];
    f.read((char *)header, 18);

    // check header
    if ((header[1]  != 0)  ||
        (header[2]  != 2  &&
         header[2]  != 3  &&
         header[2]  != 10 &&
         header[2]  != 11) ||
        (header[16] != 8  &&
         header[16] != 24 &&
         header[16] != 32))
    {
        LOG_ERROR("Invalid header.", file);
        return 0;
    }

    // skip id
    f.seekg(header[0], std::ifstream::cur);

    int w = header[12] | (header[13] << 8);
    int h = header[14] | (header[15] << 8);
    int bpp = header[16] / 8;
    int size = w*h*bpp;
    char *data = new char[size];

    if (header[2] == 2 || header[2] == 3)
    {
        // no compression, read whole data
        f.read(data, size);
    }
    else
    {
        // read rle-compressed image
        char *p = &data[0];
        char *e = &data[size];
        for(int info; p < e; p += info*bpp)
        {
            info = f.get()+1;
            if(info < 129)
            {
                f.read(p, info*bpp);
            }
            else
            {
                info -= 128;
                char tmp[bpp];
                f.read(tmp, bpp);
                for(int i = 0; i < info; i++)
                {
                    memcpy(p+i*bpp, tmp, bpp);
                }
            }
        }
    }

    f.close();

    if (bpp > 1)
    {
        // swap red and blue
        for (int i = 0; i < size; i += bpp)
        {
            char tmp = data[i+0];
            data[i+0] = data[i+2];
            data[i+2] = tmp;
        }
    }

    if (!(header[17] & 0x20))
    {
        // flip -> origin to upper left
        int line = w*bpp;
        char *tmp = new char[line];
        char *p1 = &data[0];
        char *p2 = &data[line*(h-1)];
        for (; p1 < p2; p1 += line, p2 -= line)
        {
            memcpy(tmp, p1, line);
            memcpy(p1, p2, line);
            memcpy(p2, tmp, line);
        }
        delete[] tmp;
    }

    return new Image(w, h, bpp, data);
}

// Tests string case-insensitive equality.
bool StrIEquals(const String &str1, const String &str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }

    const char *s1 = str1.c_str();
    const char *s2 = str2.c_str();

    for (; *s1 && *s2; s1++, s2++)
    {
        if (tolower(*s1) != tolower(*s2))
        {
            return false;
        }
    }
    return true;
}

Image *LoadImage(const String &file)
{
    LOG_INFO("Loading image '%'...", file);

    size_t pos = file.find_last_of('.');

    if (pos != String::npos)
    {
        String ext = file.substr(pos + 1);

        if (StrIEquals(ext, "tga"))
        {
            return LoadTGA(file);
        }
    }

    LOG_ERROR("Unknown image format.");
    return 0;
}

Image *MakeImage(int w, int h, int bpp, uint8 r, uint8 g, uint8 b, uint8 a)
{
    if (w < 1 || h < 1 || bpp < 1 || bpp > 4)
    {
        LOG_ERROR("Trying to make invalid image: w: % h: % bpp: %.", w, h, bpp);
        return 0;
    }

    uint8 color[4] = { r, g, b, a };

    int size = w*h*bpp;
    char *data = new char[size];

    char *p = &data[0];
    char *e = &data[size];
    for (; p < e; p += bpp)
    {
        memcpy(p, color, bpp);
    }

    return new Image(w, h, bpp, data);
}
