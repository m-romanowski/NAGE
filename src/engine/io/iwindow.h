#ifndef NAGE_ENGINE_IO_IWINDOW_H_
#define NAGE_ENGINE_IO_IWINDOW_H_

#include "key.h"
#include "mousebutton.h"
#include "mouse.h"
#include "keyboard.h"
#include "common/log.h"
#include "common/errormanager.h"
#include "engine/components/timer.h"
#include "engine/util/size.h"

#include <string>

namespace mr::nage
{
    /**
     * Interface for window.
     */
    class IWindow
    {
        typedef Size<float> SizeF;

    public:
        IWindow(int _width, int _height, const std::string& _title = "");
        IWindow(int _x, int _y, int _width, int _height, const std::string& _title = "");
        virtual ~IWindow();

        // Getters
        inline int x() const { return x_; }
        inline int y() const { return y_; }
        inline int width() const { return width_; }
        inline int height() const { return height_; }
        inline std::string title() const { return title_; }

        virtual void nextEvent() {}; // Get next event.
        virtual void update() {}; // Swap buffers.
        virtual void show() {}; // Show window.
        virtual void initialize() {}; // Initialize window.

        bool initialized(); // Initialize glad.
        void resize(int _width, int _height);
        void resize(const SizeF _size);

        static Timer::Clock::duration delta();
        static double deltaMs(); // Milliseconds (double)
        static Vector2f currentWindowSize();

        inline static int DEFAULT_WINDOW_WIDTH = 800;
        inline static int DEFAULT_WINDOW_HEIGHT = 600;
        inline static std::string DEFAULT_WINDOW_TITLE = "NAGE";
        inline static int DEFAULT_X_POS = 0;
        inline static int DEFAULT_Y_POS = 0;

    protected:
        // virtual void initialize() = 0;
        virtual void resizeEvent(int _width, int _height);
        virtual void keyPressEvent(const Key _key);
        virtual void keyReleaseEvent(const Key _key);
        virtual void mousePressEvent(const MouseButton _button);
        virtual void mouseReleaseEvent(const MouseButton _button);
        virtual void mouseMoveEvent(const Vector2f _movePosition);

        int x_, y_;
        int width_, height_;
        std::string title_;

        inline static Timer::Clock::time_point lastFrame_;
        inline static Vector2f currentWindowSize_;
    };
}

#endif // NAGE_ENGINE_IO_IWINDOW_H_
