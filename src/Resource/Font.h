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

#ifndef __FONT_H__
#define __FONT_H__

#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Types.h"

#include <vector>

#define MAX_TEXT_LENGTH 1024

class TextGeometry;
class IndexBuffer;
class Texture;

/// Font class
///
class Font
{
public:
    /// Initializes index data.
    Font();

    /// Builds model from given text.
    void BuildTextGeometry(const String &text, TextGeometry &textGeom);

private:
    /// Vertex struct for text geometry.
    struct Vert
    {
        Vector3 position;
        Vector2 texcoord;
    };

    /// One char's data.
    struct Char
    {
        int x, y, w, h;
        int xoffs, yoffs;
        int advance;

        Char() :
            x(0), y(0), w(0), h(0),
            xoffs(0), yoffs(0),
            advance(0)
        {
        }
    };

    std::vector<Vert> vertices;
    IndexBuffer *indexBuffer;

    /// Font data.
    int lineH, base;
    int texW, texH;
    Char chars[256];
    Texture *texture;

    friend class FontCache;
};

#endif // __FONT_H__
