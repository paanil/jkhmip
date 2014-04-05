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
#include "Logger.h"
#include "Math/Matrix4.h"
#include "Math/Math.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

Application::Application()
    : running(false)
{
    sdlReady = true;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("%", SDL_GetError());
        sdlReady = false; // SDL not ready if SDL_Init fails.
    }
}

Application::~Application()
{
    // Window must be destroyed before SDL_Quit.
    // That's why we can't rely on windows destructor.
    // TODO: find a solution to this.
    window.Destroy();

    if (sdlReady)
    {
        // Call SDL_Quit if SDL was initialized.
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

    // Set default settings.
    // TODO: read config from file.
    config.screenWidth = 800;
    config.screenHeight = 600;
    config.fullscreen = false;
    config.vsync = true;

    // Try creating the window.
    if (!window.Create(title, config.screenWidth, config.screenHeight, config.fullscreen, config.vsync))
    {
        return false;
    }

    // All good, we can allow running of the app.
    running = true;

    return true;
}

void Application::Run()
{
    OnWindowResize(config.screenWidth, config.screenHeight); // Make sure the projection is OK.
    camera.SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    cameraAngles = Vector3(0.0f, 0.0f, 0.0f);

    Uint32 lastTicks = 0;

//    // Variables for fps printing
//    Uint32 lastFPSTicks = 0;
//    Uint32 frames = 0;

    while (running)
    {
        Uint32 ticks = SDL_GetTicks();
        Uint32 delta = ticks - lastTicks;
        lastTicks = ticks;

//        // Print fps every second
//        if (ticks >= lastFPSTicks + 1000)
//        {
//            LOG_DEBUG("FPS: %", frames);
//            lastFPSTicks = ticks;
//            frames = 0;
//        }
//        frames++;

        HandleEvents();
        Update(delta / 1000.0f);
        Render();
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

            case SDL_WINDOWEVENT_RESIZED:
                OnWindowResize(e.window.data1, e.window.data2);
                break;

            default:
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

void Application::OnWindowResize(int newWidth, int newHeight)
{
    config.screenWidth = newWidth;
    config.screenHeight = newHeight;

    glViewport(0, 0, config.screenWidth, config.screenHeight);
    camera.SetPerspectiveProjection(50.0f, float(config.screenWidth)/config.screenHeight, 0.1f, 100.0f);
}

void Application::Update(float dt)
{
    const Uint8 *keys = SDL_GetKeyboardState(0);

    const float speed = 3.0f;
    const float sensitivity = 0.25f;

    // Camera movement

    Vector3 pos = camera.GetPosition();
    Vector3 right, up, look;
    camera.GetRotationAxes(right, up, look);

    Vector3 dir(0.0f, 0.0f, 0.0f);

    if (keys[SDL_SCANCODE_W])
        dir += look;
    if (keys[SDL_SCANCODE_S])
        dir -= look;
    if (keys[SDL_SCANCODE_A])
        dir -= right;
    if (keys[SDL_SCANCODE_D])
        dir += right;

    dir.SafeNormalize();
    pos += dir * (speed * dt);

    camera.SetPosition(pos);

    // Camera rotation

    int relMouseX, relMouseY;
    if (SDL_GetRelativeMouseState(&relMouseX, &relMouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        cameraAngles.y += relMouseX * sensitivity;
        cameraAngles.x += relMouseY * sensitivity;
        cameraAngles.y = Math::WrapAngleDegrees(cameraAngles.y);
        cameraAngles.x = Math::Clamp(cameraAngles.x, -85.0f, 85.0f);

        Matrix3 rot = Matrix3::RotationYXZ(cameraAngles);
        camera.SetRotation(rot);
    }
}

void Application::Render()
{
    // Code that renders the test app scene.
    // Not any proper rendering code!

    Matrix4 ortho = Matrix4::Ortho(0.0f, config.screenWidth, config.screenHeight, 0.0f, -1.0f, 1.0f);

    Matrix4 proj = camera.GetProjection();
    Matrix4 view = camera.GetViewMatrix();

    glClear(GL_COLOR_BUFFER_BIT);

    // deprecated gl begins
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(proj.data);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(view.data);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, -5.0f);
        glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-5.0f, 0.0f,  5.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 5.0f, 0.0f,  5.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 5.0f, 0.0f, -5.0f);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(ortho.data);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(10.0f, 50.0f);
        glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(10.0f, 10.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(50.0f, 10.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(50.0f, 50.0f);
    glEnd();
    // deprecated gl ends

    window.SwapBuffers();
    SDL_Delay(10); //TODO: remove
}
