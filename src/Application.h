
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
