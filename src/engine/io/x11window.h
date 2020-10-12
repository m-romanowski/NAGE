#ifndef NAGE_ENGINE_IO_X11WINDOW_H_
#define NAGE_ENGINE_IO_X11WINDOW_H_

#include "x11.h"
#include "common/log.h"
#include "common/macro.h"
#include "common/errormanager.h"
#include "engine/math/NAGEMath/nagemathvector.h"
#include "iwindow.h"

#include <iostream>
#include <cassert>
#include <unistd.h>

namespace mr::nage
{
    /**
     *  Base X11 window
     */
    class X11Window
        : public IWindow
    {
    public:
        X11Window(int _width, int _height, const std::string& _title = "undefined");
        X11Window(int _x, int _y, int _width, int _height, const std::string& _title = "undefined");
        ~X11Window();

        // TODO: move to cpp file.
        inline Display* display() { return display_; }
        inline Window window() { return window_; }

        void nextEvent() override;
        void show() override;

    private:
        void createWindow();
        void loadGLX();

    protected:
        void grabPointer();
        void ungrabPointer();
        void grabKeyboard();
        void ungrabKeyboard();
        void onMouseMove();
        void onMouseButtonPress();
        void onMouseButtonRelease();
        void onKeyPress();
        void onKeyRelease();

        Display* display_;
        Visual* visual_;
        Screen* screen_;
        int screenId_;
        Window window_, rootWindow_;
        XSetWindowAttributes windowAttribs_;
        XEvent xEvent_;

        // X11 custom components themes
        inline static Cursor TRANSPARENT_CURSOR;
    };
}

#endif // NAGE_ENGINE_IO_X11WINDOW_H_
