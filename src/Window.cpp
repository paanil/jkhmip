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

#include "Window.h"
#include "Logger.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

Window::Window() :
    window(0),
    context(0)
{
}

bool Window::Create(const String &title, int w, int h, bool fullscreen, bool vsync)
{
    // Set GL attributes.
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    int x = SDL_WINDOWPOS_UNDEFINED;
    int y = SDL_WINDOWPOS_UNDEFINED;

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    if (fullscreen)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    // Create SDL window.
    window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (window == 0)
    {
        LOG_ERROR("%", SDL_GetError());
        return false;
    }

    // Create GL context.
    context = SDL_GL_CreateContext(window);
    if (context == 0)
    {
        LOG_ERROR("%", SDL_GetError());
        return false;
    }

    // Set vsync on or off.
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);

    // Initialize GLEW (after context is created).
    GLenum error = glewInit();
    if (error != GLEW_NO_ERROR)
    {
        LOG_ERROR("%", glewGetErrorString(error));
        return false;
    }

    LOG_INFO("GL Version: %", glGetString(GL_VERSION));

    return true;
}

void Window::Destroy()
{
    if (context)
    {
        SDL_GL_DeleteContext(context);
        context = 0;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = 0;
    }
}

void Window::SwapBuffers()
{
    SDL_GL_SwapWindow(window);
}
