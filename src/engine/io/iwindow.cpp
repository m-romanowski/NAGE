#include "engine/render/glrenderengine.h"
#include "iwindow.h"

namespace NAGE
{
    Timer::Clock::time_point IWindow::lastFrame_;
    Vector2f IWindow::currentWindowSize_;

    IWindow::IWindow(int _width, int _height, const std::string& _title)
        : width_(_width),
          height_(_height),
          title_(_title)
    {

    }

    IWindow::~IWindow()
    {
        if(updateInterval_->isActive())
            updateInterval_->stop();

        if(fpsRenderTimer_->isActive())
            fpsRenderTimer_->stop();

        // delete updateInterval_;
        // delete fpsRenderTimer_;
    }

    void IWindow::resizeEvent(int _width, int _height)
    {
        width_ = _width;
        height_ = _height;
        currentWindowSize_ = Vector2f(width_, height_);

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

    }

    void IWindow::update()
    {

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
        updateInterval_ = new NAGE::Timer;
        fpsRenderTimer_ = new NAGE::Timer;

        // Game timer
        lastFrame_ = Timer::now();

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
        auto elapsed = currentTime - lastFrame_;
        lastFrame_ = Timer::now();

        return elapsed;
    }

    double IWindow::deltaMs()
    {
        return std::chrono::duration<double, std::milli>(delta()).count();
    }

    Vector2f IWindow::currentWindowSize()
    {
        return currentWindowSize_;
    }
}
