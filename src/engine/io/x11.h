#ifndef NAGE_ENGINE_IO_X11_H_
#define NAGE_ENGINE_IO_X11_H_

#include "glad/glad.h"
#include "glad/glad_glx.h"

#include <string>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace mr::nage
{
    /**
     * @brief Create a new display.
     * @return
     */
    Display* nageCreateDisplay();

    /**
     * @brief Create a new screen,
     * @param _display Display pointer
     */
    Screen* nageCreateScreen(Display* _display);

    /**
     * @brief Get current screen id.
     * @param _display Display pointer
     */
    int nageScreenId(Display* _display);

    /**
     * @brief Get root window.
     * @param _display Display pointer
     * @param _screenId Screen id
     */
    Window nageRootWindow(Display* _display, int _screenId);

    /**
     * @brief Initialize a new visual component.
     * @param _display Display pointer
     * @param _screenId Screen id
     * @return
     */
    Visual* nageCreateVisual(Display* _display, int _screenId);

    /**
     * @brief Create a new window.
     * @param _display Display pointer
     * @param _parentWindow Root window (parent)
     * @param _visual Visual component pointer
     * @param attribs Window attributes
     * @param _screenId Screen id
     * @param _x X position on the screen
     * @param _y Y position on the screen
     * @param _width Window width
     * @param _height Window height
     */
    Window nageCreateWindow(Display* _display, Window _parentWindow, Visual* _visual, XSetWindowAttributes attribs, int _screenId, int _x, int _y, int _width, int _height);

    /**
     * @brief Show window.
     * @param _display Display pointer
     * @param _window Window object
     * @param _windowTitle Optional window title
     */
    void nageMapWindow(Display* _display, Window _window, const std::string& _windowTitle = "");

    /**
     * @brief Create a new window context.
     * @param _display Display pointer
     * @param _fbc Fbcs array
     * @param _contextAttribs Context attributes
     *
     * TODO: choose best fbc - https://www.khronos.org/opengl/wiki/Tutorial:_OpenGL_3.0_Context_Creation_(GLX)
     */
    GLXContext nageCreateContext(Display* _display, GLXFBConfig* _fbc, GLint _contextAttribs[]);

    /**
     * @brief Create a new cursor theme.
     * @param _display Display pointer
     * @param _source Source pixmap
     * @param _mask Mask pixmap
     * @param _foregroundColor Foreground color
     * @param _backgroundColor BackgroundColor
     * @param _x X position
     * @param _y Y position
     */
    Cursor nageCreateCursor(Display* _display, Pixmap _source, Pixmap _mask, XColor _foregroundColor, XColor _backgroundColor, int _x = 0, int _y = 0);
}

#endif // NAGE_ENGINE_IO_X11_H_
