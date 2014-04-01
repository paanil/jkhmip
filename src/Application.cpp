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

#include "Application.h"
#include "Logging.h"
#include "Math/Matrix4.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

Application::Application()
    : running(false)
{
    sdlReady = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("%s", SDL_GetError());
        sdlReady = false;
    }
}

Application::~Application()
{
    window.Destroy();

    if (sdlReady)
    {
        SDL_Quit();
    }
}

bool Application::Init(const String &title)
{
    if (!sdlReady)
    {
        LOG_DEBUG("SDL_Init has failed.");
        return false;
    }

    config.screenWidth = 800;
    config.screenHeight = 600;
    config.fullscreen = false;
    config.vsync = true;

    if (!window.Create(title, config.screenWidth, config.screenHeight, config.fullscreen, config.vsync))
    {
        return false;
    }

    running = true;

    return true;
}

void Application::Run()
{
    Matrix4 ortho = Matrix4::Ortho(config.screenWidth, config.screenHeight, -1.0f, 1.0f);
    Matrix4 persp = Matrix4::Perspective(50.0f, float(config.screenWidth) / config.screenHeight, 0.1f, 100.0f);

    Matrix4 view = (Matrix4::Translation(-8.0f, 4.0f, -10.0f) *
                    Matrix4::Rotation(0.0f, 1.0f, 0.0f, 35.0f) *
                    Matrix4::Rotation(1.0f, 0.0f, 0.0f, 15.0f)).InverseTR();

//        Uint32 lastTicks = 0;
//        Uint32 frames = 0;

    while (running)
    {
//            Uint32 ticks = SDL_GetTicks();
//
//            if (ticks >= lastTicks + 1000)
//            {
//                LOG_DEBUG("FPS: %d", frames);
//                lastTicks = ticks;
//                frames = 0;
//            }
//
//            frames++;

        HandleEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        // deprecated gl begins
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(ortho.data);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float x = -390.0f;
        float y = 250.0f;

        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(x,  y);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(x, y + 40.0f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(x + 40.0f, y + 40.0f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(x + 40.0f, y);
        glEnd();

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(persp.data);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(view.data);

        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, -5.0f);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-5.0f, 0.0f,  5.0f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 5.0f, 0.0f,  5.0f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 5.0f, 0.0f, -5.0f);
        glEnd();
        // deprecated gl ends

        window.SwapBuffers();
        SDL_Delay(10); //TODO: remove
    }
}

void Application::HandleEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                running = false;
                break;
            }
            break;

        case SDL_KEYDOWN:
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                running = false;
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}
