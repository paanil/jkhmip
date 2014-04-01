
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Types.h"

struct SDL_Window;
#define GL_Context void * // "Forward declaring" SDL_GLContext which is actually a void pointer

/// Simple window class.
class Window
{
public:
    Window();

    /// Creates a window with SDL and initializes GLEW.
    ///
    /// \return false on fail
    bool Create(const String &title, int w, int h, bool fullscreen, bool vsync);

    /// Must be called before SDL_Quit() if window has been created.
    /// Safe to call even if window  hasn't been created.
    void Destroy();

    void SwapBuffers();

private:
    SDL_Window *window;
    GL_Context context;
};

#endif // __WINDOW_H__
