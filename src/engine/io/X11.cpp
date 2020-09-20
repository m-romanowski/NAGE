#include "X11.h"

namespace NAGE
{
    X11::X11()
    {
        // Create a new display.
        display_ = XOpenDisplay(nullptr);
        if(display_ == nullptr)
        {
            std::error_code code = ERROR::X11_FAILED_DISPLAY_INITIALIZATION;
            Log::critical(code.message());
        }

        // X11 error handler.
        XSetErrorHandler(XlibErrorHandler);

        // Get root window.
        window_ = XDefaultRootWindow(display_);

        XGrabPointer(display_, window_, 1, PointerMotionMask, GrabModeAsync, GrabModeAsync,
            None, None, CurrentTime);

        while(true)
        {
            XNextEvent(display_, &xEvent_);

            switch (xEvent_.type)
            {
                case MotionNotify:
                    cursorX_ = xEvent_.xmotion.x_root;
                    cursorY_ = xEvent_.xmotion.y_root;
                    break;
            }
        }
    }

    X11::~X11()
    {
        XCloseDisplay(display_);
    }

    int X11::XlibErrorHandler(Display* _display, XErrorEvent* _event)
    {
        NAGE_UNUSED(_display);
        NAGE_UNUSED(_event);

        NAGE::Log::error("Enexpected error: " + std::string(reinterpret_cast<char*>(_event->error_code)));
        return True;
    }

    Vector2f X11::cursorPosition()
    {
        return Vector2f(cursorX_, cursorY_);
    }

    int X11::cursorX()
    {
        return cursorX_;
    }

    int X11::cursorY()
    {
        return cursorY_;
    }
}
