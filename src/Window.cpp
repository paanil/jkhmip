
#include "Window.h"
#include "Logging.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

Window::Window() :
    window(0),
    context(0)
{
}

bool Window::Create(const String &title, int w, int h, bool fullscreen, bool vsync)
{
    // set gl attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    int x = SDL_WINDOWPOS_UNDEFINED;
    int y = SDL_WINDOWPOS_UNDEFINED;

    Uint32 flags = SDL_WINDOW_OPENGL;
    if (fullscreen)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    // create sdl window
    window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (window == 0)
    {
        LOG_ERROR("%s", SDL_GetError());
        return false;
    }

    // create gl context
    context = SDL_GL_CreateContext(window);
    if (context == 0)
    {
        LOG_ERROR("%s", SDL_GetError());
        return false;
    }

    // set vsync on or off
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);

    // initialize glew
    GLenum error = glewInit();
    if (error != GLEW_NO_ERROR)
    {
        LOG_ERROR("%s", glewGetErrorString(error));
        return false;
    }

    LOG_INFO("GL Version: %s", glGetString(GL_VERSION));

    return true;
}

void Window::Destroy()
{
    if (context)
    {
        SDL_GL_DeleteContext(context);
        context = 0;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = 0;
    }
}

void Window::SwapBuffers()
{
    SDL_GL_SwapWindow(window);
}
