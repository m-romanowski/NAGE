#include "x11.h"

namespace mr::nage
{
    Display* nageCreateDisplay()
    {
        return XOpenDisplay(nullptr);
    }

    Screen* nageCreateScreen(Display* _display)
    {
        return DefaultScreenOfDisplay(_display);
    }

    int nageScreenId(Display* _display)
    {
        return DefaultScreen(_display);
    }

    Window nageRootWindow(Display* _display, int _screenId)
    {
        return RootWindow(_display, _screenId);
    }

    Visual* nageCreateVisual(Display* _display, int _screenId)
    {
        return DefaultVisual(_display, _screenId);
    }

    Window nageCreateWindow(Display* _display, Window _parentWindow, Visual* _visual, XSetWindowAttributes attribs, int _screenId, int _x, int _y, int _width, int _height)
    {
        return XCreateWindow(_display, _parentWindow, _x, _y,_width, _height, 0,
            DefaultDepth(_display, _screenId), InputOutput, _visual, CWColormap | CWEventMask, &attribs);
    }

    void nageMapWindow(Display* _display, Window _window, const std::string& _windowTitle)
    {
        XMapWindow(_display, _window);
        XStoreName(_display, _window, _windowTitle.c_str());
    }

    GLXContext nageCreateContext(Display* _display, GLXFBConfig* _fbc, GLint _contextAttribs[])
    {
        return glXCreateContextAttribsARB(_display, _fbc[0], NULL, True, _contextAttribs);
    }

    Cursor nageCreateCursor(Display* _display, Pixmap _source, Pixmap _mask, XColor _foregroundColor, XColor _backgroundColor, int _x, int _y)
    {
        return XCreatePixmapCursor(_display, _source, _mask, &_foregroundColor, &_backgroundColor, _x, _y);
    }
}
