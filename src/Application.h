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

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Window.h"

class Application
{
public:
    Application();
    ~Application();

    bool Init(const String &title);
    void Run();

private:
    void HandleEvents();

private:
    struct Config
    {
        int screenWidth;
        int screenHeight;
        bool fullscreen;
        bool vsync;
    };

    Config config;
    Window window;
    bool sdlReady;
    bool running;
};

#endif // __APPLICATION_H__
