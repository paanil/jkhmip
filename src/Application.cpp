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
#include "Render/Graphics.h"
#include "Logger.h"
#include "Conf.h"

#include <SDL2/SDL.h>

Application::Application()
{
    sdlReady = true;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("%", SDL_GetError());
        sdlReady = false; // SDL not ready if SDL_Init fails.
    }

    running = false;
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
        return false;

    // Try creating the window.
    if (!window.Create(title,
                       Config::getInt("mainScreen_Width"),
                       Config::getInt("mainScreen_Height"),
                       Config::getBool("mainScreen_FullScreen"),
                       Config::getBool("mainScreen_vsync")))
    {
        return false;
    }

    // Initialize graphics state.
    Graphics::InitState();

    // Initialize resource manager.
    resources.Init();

    // All good, we can allow running of the app.
    running = true;

    return true;
}

void Application::Run()
{
    OnWindowResize(Config::getInt("mainScreen_Width"), Config::getInt("mainScreen_Height"));

    resources.LoadScene(scene, "test.scene");

    Scene::Camera *camera = scene.CreateCamera();
    camera->SetParameters(50.0f, 0.1f, 100.0f);
    renderer.SetCamera(camera);
    cam.SetCamera(camera);

    Scene::Object *sword = scene.CreateObject();
    sword->SetModel(resources.GetModel("sword.obj"));
    sword->SetParent(camera);
    sword->SetPosition(Vector3(0.3f, -0.3f, 0.6f));
    sword->SetRotation(Matrix3::RotationX(25.0f) * Matrix3::RotationY(-17.5f));


    text.SetRelativePosition(Vector2(10.0f, 10.0f));
    text.SetFont(resources.GetFont("LiberationSans_24_Bold.fnt"));
    text.SetText("FPS: ");
    text.SetColor(Vector4(1.0f, 1.0f, 0.0f, 1.0f));


    Uint32 lastTicks = 0;

    // Variables for fps counter
    Uint32 lastFPSTicks = 0;
    Uint32 frames = 0;
    String fps;

    while (running)
    {
        Uint32 ticks = SDL_GetTicks();
        Uint32 delta = ticks - lastTicks;
        lastTicks = ticks;

        // Update fps every second
        if (ticks >= lastFPSTicks + 1000)
        {
//            LOG_DEBUG("FPS: %", frames);
            Format(fps, "FPS: %", frames);
            text.SetText(fps);
            lastFPSTicks = ticks;
            frames = 0;
        }
        frames++;

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

void Application::OnWindowResize(int w, int h)
{
    Config::setInt("mainScreen_Width",w);
    Config::setInt("mainScreen_Heigth",h);

    renderer.SetViewport(0, 0, w, h);
    proj2d = Matrix4::Ortho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
}

void Application::Update(float dt)
{
    cam.Update(dt);
}

void Application::Render()
{
    renderer.Render(scene);

    // Render fps
    const TextGeometry &geometry = text.GetGeometry();
    Vector2 pos = text.GetAbsolutePosition();
    Shader *shader = resources.GetShader("text.shader");

    Graphics::Clear(CLEAR_DEPTH);
    Graphics::ResetState();
    Graphics::SetBlendMode(BM_MIX);
    Graphics::SetTexture(geometry.GetFontTexture(), 0);
    Graphics::SetShader(shader);
    shader->SetProjMatrix(proj2d);
    shader->SetTranslation(Vector3(pos.x, pos.y, 0.0f));
    shader->SetColor(text.GetColor());
    Graphics::SetVertexBuffer(geometry.GetVertexBuffer());
    Graphics::SetIndexBuffer(geometry.GetIndexBuffer());
    Graphics::DrawTriangles(0, geometry.GetIndexCount());

    // Draw screen
    window.SwapBuffers();
//    SDL_Delay(10); //TODO: remove
}
