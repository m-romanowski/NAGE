#include "engine/render/glrenderengine.h"
#include "iwindow.h"

namespace NAGE
{
    Timer::Clock::time_point IWindow::lastFrame;

    IWindow::IWindow(int _width, int _height, const std::string& _title)
        : mWidth(_width),
          mHeight(_height),
          mTitle(_title)
    {

    }

    IWindow::~IWindow()
    {
        if(updateInterval->isActive())
            updateInterval->stop();

        if(fpsRenderTimer->isActive())
            fpsRenderTimer->stop();

        // delete updateInterval;
        // delete fpsRenderTimer;
    }

    void IWindow::resizeEvent(int _width, int _height)
    {
        mWidth = _width;
        mHeight = _height;

        // Update view and projection (perspective) aspect ratio = width / height.
        GLRenderEngine::projection().setAspectRatio(_width, _height);
        glViewport(0, 0, _width, _height);
    }

    void IWindow::keyPressEvent(Key _key)
    {
        Keyboard::registerKeyPress(_key);
    }

    void IWindow::keyReleaseEvent(Key _key)
    {
        Keyboard::registerKeyRelease(_key);
    }

    void IWindow::mousePressEvent(MouseButton _button)
    {
        Mouse::registerMousePress(_button);
    }

    void IWindow::mouseReleaseEvent(MouseButton _button)
    {
        Mouse::registerMouseRelease(_button);
    }

    void IWindow::mouseMoveEvent()
    {

    }

    void IWindow::sync()
    {
        //
    }

    void IWindow::update()
    {
        //
    }

    bool IWindow::initialized()
    {
        if(!gladLoadGL())
        {
            std::error_code code = ERROR::FAILED_GLAD_INITIALIZATION;
            Log::error(code.message());

            return false;
        }

        // Updates interval, FPS timer
        updateInterval = new NAGE::Timer;
        fpsRenderTimer = new NAGE::Timer;

        // Game timer
        lastFrame = Timer::now();

        return true;
    }

    /* Compute delta time between current (frame) time and last (frame) time.
     * Allows to make animations / movement not based on FPS (frames per second) -
     * - synchronize movement regardless of the platform on which we run the program.
     *
     * movement += Vector3(dx, dy, dz) * delta
     */
    Timer::Clock::duration IWindow::delta()
    {
        auto currentTime = Timer::now();
        auto elapsed = currentTime - lastFrame;
        lastFrame = Timer::now();

        return elapsed;
    }

    double IWindow::deltaMs()
    {
        return std::chrono::duration<double, std::milli>(delta()).count();
    }
}
