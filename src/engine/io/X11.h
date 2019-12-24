#ifndef NAGE_ENGINE_X11_H_
#define NAGE_ENGINE_X11_H_

#include "common/log.h"
#include "common/macro.h"
#include "common/errormanager.h"
#include "engine/math/NAGEMath/nagemathvector.h"

#include <X11/Xlib.h>
#include <iostream>
#include <cassert>
#include <unistd.h>

namespace NAGE
{
    class X11
    {
    public:
        X11();
        ~X11();

        // Getters
        Vector2f cursorPosition();
        int cursorX();
        int cursorY();

    private:
        static int XlibErrorHandler(Display* _display, XErrorEvent* _event);

        Display* mDisplay;
        Window mWindow;
        XEvent mXEvent;
        int mCursorX, mCursorY;
    };
}

#endif // NAGE_ENGINE_X11_H_
