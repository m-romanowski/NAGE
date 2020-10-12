#include "x11window.h"

namespace mr::nage
{
    X11Window::X11Window(int _width, int _height, const std::string& _title)
        : IWindow(_width, _height, _title)
    {
        createWindow();
    }

    X11Window::X11Window(int _x, int _y, int _width, int _height, const std::string& _title)
        : IWindow(_x, _y, _width, _height, _title)
    {
        createWindow();
    }

    X11Window::~X11Window()
    {
        XFree(visual_);
        XFreeColormap(display_, windowAttribs_.colormap);
        XDestroyWindow(display_, window_);
        XFree(screen_);
        XCloseDisplay(display_);
    }

    void X11Window::nextEvent()
    {
        XNextEvent(display_, &xEvent_);
    }

    void X11Window::show()
    {
        nageMapWindow(display_, window_, title_);
    }

    void X11Window::createWindow()
    {
        // Create a new display.
        display_ = nageCreateDisplay();
        if(!display_)
        {
            std::error_code code = ERROR::X11_FAILED_DISPLAY_INITIALIZATION;
            Log::critical(code.message());
            return;
        }

        screen_ = nageCreateScreen(display_);
        screenId_ = nageScreenId(display_);

        rootWindow_ = nageRootWindow(display_, screenId_);
        visual_ = nageCreateVisual(display_, screenId_);

        Colormap colormap = XCreateColormap(display_, rootWindow_, visual_, AllocNone);
        windowAttribs_.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;
        windowAttribs_.colormap = colormap;

        window_ = nageCreateWindow(display_, rootWindow_, visual_, windowAttribs_, screenId_, x_, y_, width_, height_);
        if(!window_)
        {
            std::error_code code = ERROR::X11_FAILED_DISPLAY_INITIALIZATION;
            Log::critical(code.message());
            return;
        }

        XSync(display_, False);

        loadGLX();

        // Component themes
        XColor black;
        char empty[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        Pixmap transparentPixmap = XCreateBitmapFromData(display_, window_, empty, 8, 8);
        TRANSPARENT_CURSOR = nageCreateCursor(display_, transparentPixmap, transparentPixmap, black, black);
    }

    void X11Window::loadGLX()
    {
        if(!gladLoadGLX(display_, screenId_))
        {
            std::error_code code = ERROR::X11_FAILED_DISPLAY_INITIALIZATION;
            Log::critical(code.message());
        }
    }

    void X11Window::grabPointer()
    {
        XGrabPointer(display_, window_, true, ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask |
            EnterWindowMask | LeaveWindowMask, GrabModeAsync,GrabModeAsync, None, TRANSPARENT_CURSOR, CurrentTime);
    }

    void X11Window::grabKeyboard()
    {
        XGrabKeyboard(display_, window_, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }

    void X11Window::ungrabPointer()
    {
        XUngrabPointer(display_, CurrentTime);
    }

    void X11Window::ungrabKeyboard()
    {
        XUngrabKeyboard(display_, CurrentTime);
    }

    void X11Window::onMouseMove()
    {
        mouseMoveEvent(Vector2f(xEvent_.xmotion.x_root, xEvent_.xmotion.y_root));
    }

    void X11Window::onMouseButtonPress()
    {
        mousePressEvent(static_cast<nage::MouseButton>(xEvent_.xbutton.button));
    }

    void X11Window::onMouseButtonRelease()
    {
        mouseReleaseEvent(static_cast<nage::MouseButton>(xEvent_.xbutton.button));
    }

    void X11Window::onKeyPress()
    {
        keyPressEvent(static_cast<nage::Key>(xEvent_.xkey.keycode));
    }

    void X11Window::onKeyRelease()
    {
        keyReleaseEvent(static_cast<nage::Key>(xEvent_.xkey.keycode));
    }
}
