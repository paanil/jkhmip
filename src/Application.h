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
#include "Resource/ShaderCache.h"
#include "Resource/TextureCache.h"
#include "Resource/MaterialCache.h"
#include "Resource/ModelCache.h"
#include "Resource/FontCache.h"
#include "Scene/Scene.h"

/// Application class. There should be only one instance at a time.
///
class Application
{
public:
    /// Constructor and destructor.
    Application();
    ~Application();

    /// Initializes application.
    /// \param title Title for the application window.
    /// \return false on fail.
    bool Init(const String &title);
    /// Runs the application. Init must be called
    /// before application can be run.
    void Run();

private:
    /// Polls events and handles (some of) them.
    void HandleEvents();

    /// Event handler for window resize.
    void OnWindowResize(int w, int h);

    /// Updates the "simulation".
    void Update(float dt);

    /// Renders the scene.
    void Render();

private:
    /// Structure for application settings.
    struct Config
    {
        int screenWidth;
        int screenHeight;
        bool fullscreen;
        bool vsync;
    };

    /// Application settings.
    Config config;
    /// Application window.
    Window window;
    /// True if SDL_Init succeeds.
    bool sdlReady;
    /// The application stays inside
    /// Run() as long as this is true.
    bool running;

    /* Members for the test app */
    ShaderCache     shaderCache;
    TextureCache    textureCache;
    MaterialCache   materialCache;
    ModelCache      modelCache;
    FontCache       fontCache;

    Scene scene;
    SceneCamera *camera;
    Vector3 cameraAngles;

    Matrix4 proj2d;
    Model text;
};

#endif // __APPLICATION_H__
