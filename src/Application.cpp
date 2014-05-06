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
#include "Conf.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

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

    // All good, we can allow running of the app.
    running = true;

    return true;
}

void Application::Run()
{
    shaderCache.SetDirectory(Config::getString("Shader_location"));
    textureCache.SetDirectory(Config::getString("Texture_location"));

    materialCache.SetDirectory(Config::getString("Material_location"));
    materialCache.SetShaderCache(shaderCache);
    materialCache.SetTextureCache(textureCache);

    modelCache.SetDirectory(Config::getString("Model_location"));
    modelCache.SetMaterialCache(materialCache);

    fontCache.SetDirectory(Config::getString("Font_location"));
    fontCache.SetTextureCache(textureCache);
    fontCache.InitIndexBuffer();

    sceneLoader.SetDirectory(Config::getString("Scene_location"));
    sceneLoader.SetModelCache(modelCache);


    sceneLoader.LoadScene(scene, "test.scene");

    camera = scene.CreateCamera();
    camera->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    OnWindowResize(Config::getInt("mainScreen_Width"), Config::getInt("mainScreen_Height")); // Make sure the projection is OK.

    SceneObject *sword = scene.CreateObject();
    sword->SetModel(modelCache.Get("sword.obj"));
    sword->SetParent(camera);
    sword->SetPosition(Vector3(0.3f, -0.3f, 0.6f));
    sword->SetRotation(Matrix3::RotationX(25.0f) * Matrix3::RotationY(-17.5f));

    cam.SetCamera(camera);


    text.SetRelativePosition(Vector2(10.0f, 10.0f));
    text.SetFont(fontCache.Get("LiberationSans_24_Bold.fnt"));
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

    glViewport(0, 0, w, h);
    camera->SetPerspectiveProjection(50.0f, float(w)/h, 0.1f, 100.0f);
    proj2d = Matrix4::Ortho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
}

void Application::Update(float dt)
{
    cam.Update(dt);
}

void Application::Render()
{
    renderer.Render(scene, camera);

    // Render fps
    glClear(GL_DEPTH_BUFFER_BIT);

    Shader *shader = shaderCache.Get("text.shader");
    shader->Use();
    shader->SetProjMatrix(proj2d);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    text.Render(shader);

    glDisable(GL_BLEND);

    // Draw screen
    window.SwapBuffers();
//    SDL_Delay(10); //TODO: remove
}
