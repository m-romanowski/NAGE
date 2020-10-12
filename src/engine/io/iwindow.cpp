#include "engine/render/glrenderengine.h"
#include "iwindow.h"

namespace mr::nage
{
    IWindow::IWindow(int _width, int _height, const std::string& _title)
        : width_(_width),
          height_(_height),
          title_(_title)
    {

    }

    IWindow::IWindow(int _x, int _y, int _width, int _height, const std::string& _title)
        : x_(_x),
          y_(_y),
          width_(_width),
          height_(_height),
          title_(_title)
    {

    }

    IWindow::~IWindow()
    {

    }

    void IWindow::resizeEvent(int _width, int _height)
    {
        width_ = _width;
        height_ = _height;

        currentWindowSize_.setX(_width);
        currentWindowSize_.setY(_height);

        // Update view and projection (perspective) aspect ratio = width / height.
        GLRenderEngine::projection().setAspectRatio(_width, _height);
        glViewport(0, 0, _width, _height);
    }

    void IWindow::keyPressEvent(const Key _key)
    {
        Keyboard::registerKeyPress(_key);
    }

    void IWindow::keyReleaseEvent(const Key _key)
    {
        Keyboard::registerKeyRelease(_key);
    }

    void IWindow::mousePressEvent(const MouseButton _button)
    {
        Mouse::registerMousePress(_button);
    }

    void IWindow::mouseReleaseEvent(const MouseButton _button)
    {
        Mouse::registerMouseRelease(_button);
    }

    void IWindow::mouseMoveEvent(const Vector2f _movePosition)
    {
        Mouse::registerMouseMove(_movePosition);
    }

    bool IWindow::initialized()
    {
        // Render lock timer
        lastFrame_ = Timer::now();
        return true;
    }

    void IWindow::resize(int _width, int _height)
    {
        resizeEvent(_width, _height);
    }

    void IWindow::resize(const SizeF _size)
    {
        resizeEvent(_size.width(), _size.height());
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
