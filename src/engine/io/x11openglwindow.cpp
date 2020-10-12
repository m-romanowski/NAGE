#include "x11openglwindow.h"

namespace mr::nage
{
    X11OpenGLWindow::X11OpenGLWindow(int _width, int _height, const std::string& _title, const std::vector<GLint> _visualAttribs)
        : X11Window(_width, _height, _title)
    {
        std::copy(_visualAttribs.begin(), _visualAttribs.end(), std::back_inserter(visualAttribs_));
        initializeContext();
    }

    X11OpenGLWindow::X11OpenGLWindow(int _x, int _y, int _width, int _height, const std::string& _title, const std::vector<GLint> _visualAttribs)
        : X11Window(_x, _y, _width, _height, _title)
    {
        std::copy(_visualAttribs.begin(), _visualAttribs.end(), std::back_inserter(visualAttribs_));
        initializeContext();
    }

    X11OpenGLWindow::~X11OpenGLWindow()
    {
        glXMakeCurrent(display_, 0, 0);
        glXDestroyContext(display_, context_);
    }

    void X11OpenGLWindow::initialize()
    {
        glXMakeCurrent(display_, window_, context_);

        if(!gladLoadGL())
        {
            std::error_code code = ERROR::FAILED_GLAD_INITIALIZATION;
            Log::error(code.message());
        }
    }

    void X11OpenGLWindow::nextEvent()
    {
        while(XPending(display_))
        {
            XNextEvent(display_, &xEvent_);
            switch (xEvent_.type)
            {
                // Window events
                case Expose: onWindowResize(); break;
                // Mouse events
                case MotionNotify: onMouseMove(); break;
                case ButtonPress: onMouseButtonPress(); break;
                case ButtonRelease: onMouseButtonRelease(); break;
                // Keyboard events
                case KeyPress:
                    // TMP
                    if(static_cast<nage::Key>(xEvent_.xkey.keycode) == Key::X11_KEY_LEFT_CTRL)
                    {
                        if(!grabbed)
                        {
                            grabPointer();
                            grabKeyboard();
                            grabbed = true;
                        }
                        else
                        {
                            ungrabPointer();
                            ungrabKeyboard();
                            grabbed = false;
                        }
                    }

                    onKeyPress();
                    break;
                case KeyRelease: onKeyRelease(); break;
            }
        }
    }

    void X11OpenGLWindow::update()
    {
        glXSwapBuffers(display_, window_); // Enabled `GLX_DOUBLEBUFFER`.
    }

    void X11OpenGLWindow::updateSingle()
    {
        glFlush(); // Disabled `GLX_DOUBLEBUFFER`.
    }

    void X11OpenGLWindow::initializeContext()
    {
        int numFbc = 0;
        GLXFBConfig* fbc = glXChooseFBConfig(display_, screenId_, visualAttribs_.data(), &numFbc);

        GLint contextAttributes[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, GL_CONTEXT_VERSION_MAJOR,
            GLX_CONTEXT_MINOR_VERSION_ARB, GL_CONTEXT_VERSION_MINOR,
            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            None
        };

        if(!XInitThreads())
        {
            std::error_code code = ERROR::X11_FAILED_DISPLAY_INITIALIZATION;
            Log::critical(code.message());
            return;
        }

        context_ = nageCreateContext(display_, fbc, contextAttributes);
        if(!context_)
        {
            std::error_code code = ERROR::X11_FAILED_DISPLAY_INITIALIZATION;
            Log::critical(code.message());
            return;
        }
    }

    void X11OpenGLWindow::onWindowResize()
    {
        XWindowAttributes attribs;
        XGetWindowAttributes(display_, window_, &attribs);
        resizeEvent(attribs.width, attribs.height);
    }
}
