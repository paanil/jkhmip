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
#include "Resource/ResourceManager.h"
#include "Render/SceneRenderer.h"
#include "Scene/Scene.h"
#include "CameraController.h"
#include "UI/Text.h"

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

    /// Updates the "simulation".
    void Update(float dt);

    /// Renders the scene.
    void Render();

private:
    /// Application window.
    Window window;
    /// True if SDL_Init succeeds.
    bool sdlReady;
    /// The application stays inside
    /// Run() as long as this is true.
    bool running;

    /* Members for the test app */
    ResourceManager resources;

    Scene::Scene scene;
    SceneRenderer renderer;

    CameraController cam;

    Matrix4 proj2d;
    UI::Text text;
};

#endif // __APPLICATION_H__
