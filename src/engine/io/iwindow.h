#ifndef NAGE_ENGINE_IO_IWINDOW_H_
#define NAGE_ENGINE_IO_IWINDOW_H_

#include "glad/glad.h"

#include "key.h"
#include "mousebutton.h"
#include "mouse.h"
#include "keyboard.h"
#include "common/log.h"
#include "common/errormanager.h"
#include "engine/components/timer.h"

#include <string>

namespace NAGE
{
    /* Interface for OpenGL window.
     */
    class IWindow
    {
    public:
        IWindow(int _width, int _height, const std::string& _title = "");
        virtual ~IWindow();

        // Getters
        inline int width() const { return mWidth; }
        inline int height() const { return mHeight; }
        inline std::string title() const { return mTitle; }

        // Setters
        inline void setWidth(int _width) { mWidth = _width; }
        inline void setHeight(int _height) { mHeight = _height; }
        inline void setTitle(const std::string& _title) { mTitle = _title; }

        virtual void sync(); // Synchronize updates (fps limiter).
        virtual void update(); // Swap buffers.
        bool initialized(); // Initialize glad.

        static Timer::Clock::duration delta();
        static double deltaMs(); // Milliseconds (double)
        static Vector2f currentWindowSize();

    protected:
        // virtual void initialize() = 0;
        virtual void resizeEvent(int _width, int _height);
        virtual void keyPressEvent(Key _key);
        virtual void keyReleaseEvent(Key _key);
        virtual void mousePressEvent(MouseButton _button);
        virtual void mouseReleaseEvent(MouseButton _button);
        virtual void mouseMoveEvent();

        int mWidth, mHeight;
        std::string mTitle;
        Timer *updateInterval, *fpsRenderTimer;

        static Timer::Clock::time_point mLastFrame;
        static Vector2f mCurrentWindowSize;
    };
}

#endif // NAGE_ENGINE_IO_IWINDOW_H_
