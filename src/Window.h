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

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Types.h"

// Forward declarations.
struct SDL_Window;
typedef void *SDL_GLContext;

/// Simple window class.
///
class Window
{
public:
    /// Constructor sets members to 0.
    Window();

    /// Creates a window with SDL and initializes GLEW.
    ///
    /// \return false on fail
    bool Create(const String &title, int w, int h, bool fullscreen, bool vsync);

    /// Must be called before SDL_Quit() if window has been created.
    /// Safe to call even if window  hasn't been created.
    void Destroy();

    /// Updates the screen.
    void SwapBuffers();

private:
    SDL_Window *window;
    SDL_GLContext context;
};

#endif // __WINDOW_H__
