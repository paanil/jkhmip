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

#include "FrameBuffer.h"
#include "Texture.h"

#include <GL/glew.h>

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &framebuf);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &framebuf);
}

void FrameBuffer::AttachColorTex2D(Texture *colorTex)
{
    GLuint tex = colorTex ? colorTex->texture : 0;
    glBindFramebuffer(GL_FRAMEBUFFER, framebuf);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
}

void FrameBuffer::AttachDepthTex2D(Texture *depthTex)
{
    GLuint tex = depthTex ? depthTex->texture : 0;
    glBindFramebuffer(GL_FRAMEBUFFER, framebuf);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex, 0);
}

void FrameBuffer::Bind(bool depthOnly)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuf);
    if (depthOnly)
    {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
    glReadBuffer(GL_BACK);
}
