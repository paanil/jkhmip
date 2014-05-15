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

#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include "../Types.h"

class Texture;

class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void AttachColorTex2D(Texture *colorTex);
    void AttachDepthTex2D(Texture *depthTex);

    void Bind(bool depthOnly = false);

    void Unbind();

private:
    uint framebuf;
};

#endif // __FRAMEBUFFER_H__
