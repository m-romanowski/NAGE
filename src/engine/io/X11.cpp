#include "X11.h"

namespace NAGE
{
    X11::X11()
    {
        // Create a new display.
        mDisplay = XOpenDisplay(nullptr);
        if(mDisplay == nullptr)
        {
            std::error_code code = ERROR::X11_FAILED_DISPLAY_INITIALIZATION;
            Log::critical(code.message());
        }

        // X11 error handler.
        XSetErrorHandler(XlibErrorHandler);

        // Get root window.
        mWindow = XDefaultRootWindow(mDisplay);

        XGrabPointer(mDisplay, mWindow, 1, PointerMotionMask, GrabModeAsync, GrabModeAsync,
            None, None, CurrentTime);

        while(true)
        {
            XNextEvent(mDisplay, &mXEvent);

            switch (mXEvent.type)
            {
                case MotionNotify:
                    mCursorX = mXEvent.xmotion.x_root;
                    mCursorY = mXEvent.xmotion.y_root;
                    break;
            }
        }
    }

    X11::~X11()
    {
        XCloseDisplay(mDisplay);
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
        return Vector2f(mCursorX, mCursorY);
    }

    int X11::cursorX()
    {
        return mCursorX;
    }

    int X11::cursorY()
    {
        return mCursorY;
    }
}
