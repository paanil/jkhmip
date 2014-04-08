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

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "../Types.h"

/// Image class.
///
class Image
{
public:
    /// Initializes image with given data.
    /// Takes ownership of the data pointer.
    Image(int w, int h, int bpp, char *data);
    /// Releases the data.
    ~Image();

    /// Getters for members.
    int GetWidth() const;
    int GetHeight() const;
    int GetBytesPerPixel() const;
    const char *GetData() const;

private:
    int w, h, bpp;
    char *data;
};

/// Loads an image from file.
///
/// Only 8-bit gray scale and 24- or 32-bit true color
/// TGA images with no/rle compression are supported.
/// \param file Path to the image file.
/// \return Pointer to the loaded image. You need to delete it! (or wrap in a smart pointer)
Image *LoadImage(const String &file);

/// Creates an image filled with given color.
///
/// \param w Width of the image
/// \param h Height of the image
/// \param bpp BytesPerPixel of the image
/// \param r Red component of the fill color.
/// \param g Green component of the fill color.
/// \param b Blue component of the fill color.
/// \param a Alpha component of the fill color.
/// \return Pointer to the created image. You need to delete it! (or wrap in a smart pointer)
Image *MakeImage(int w, int h, int bpp, uint8 r, uint8 g, uint8 b, uint8 a);

#endif // __IMAGE_H__
