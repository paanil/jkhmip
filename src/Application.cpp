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
#include "Math/Math.h"
#include "Logger.h"

#include "Resource/ShaderCache.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

Application::Application() :
    running(false),
    modelCache(textureCache)
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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    OnWindowResize(config.screenWidth, config.screenHeight); // Make sure the projection is OK.
    scene.GetCamera()->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    cameraAngles = Vector3(0.0f, 0.0f, 0.0f);

    shaderCache.SetDirectory("Data/Shaders/");
    textureCache.SetDirectory("Data/Textures/");
    modelCache.SetDirectory("Data/Models/");

    shader = shaderCache.Get("default.shader");

    SceneObject *ground = scene.CreateObject();
    ground->SetModel(modelCache.Get("ground.obj"));

    SceneObject *house = scene.CreateObject();
    house->SetModel(modelCache.Get("house.obj"));
    house->SetPosition(Vector3(-3.0f, -0.75f, 3.0f));
    house->SetRotation(Matrix3::RotationY(-15.0f));

    SceneObject *sword = scene.CreateObject();
    sword->SetModel(modelCache.Get("sword.obj"));
    sword->SetParent(scene.GetCamera());
    sword->SetPosition(Vector3(0.3f, -0.3f, 0.6f));
    sword->SetRotation(Matrix3::RotationX(25.0f) * Matrix3::RotationY(-17.5f));

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

    glViewport(0, 0, newWidth, newHeight);
    scene.GetCamera()->SetPerspectiveProjection(50.0f, float(newWidth)/newHeight, 0.1f, 100.0f);
}

void Application::Update(float dt)
{
    const Uint8 *keys = SDL_GetKeyboardState(0);

    const float speed = 6.0f;
    const float sensitivity = 0.25f;

    // Camera movement
    SceneCamera *camera = scene.GetCamera();

    Vector3 pos = camera->GetPosition();
    Vector3 right, up, look;
    camera->GetBasisVectors(right, up, look);

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

    camera->SetPosition(pos);

    // Camera rotation

    int relMouseX, relMouseY;
    if (SDL_GetRelativeMouseState(&relMouseX, &relMouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);

        cameraAngles.y += relMouseX * sensitivity;
        cameraAngles.x += relMouseY * sensitivity;
        cameraAngles.y = Math::WrapAngleDegrees(cameraAngles.y);
        cameraAngles.x = Math::Clamp(cameraAngles.x, -85.0f, 85.0f);

        Matrix3 rot = Matrix3::RotationYXZ(cameraAngles);
        camera->SetRotation(rot);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

void Application::Render()
{
    // Code that renders the test app scene.
    // Not any proper rendering code!

    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Use();
    shader->SetTime(SDL_GetTicks() / 1000.0f);

    scene.Render(shader);

    window.SwapBuffers();
    SDL_Delay(10); //TODO: remove
}
