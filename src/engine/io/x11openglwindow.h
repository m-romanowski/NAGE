#ifndef NAGE_ENGINE_IO_X11OPENGLWINDOW_H_
#define NAGE_ENGINE_IO_X11OPENGLWINDOW_H_

#include "x11window.h"
#include "engine/components/const.h"

#include <vector>

namespace mr::nage
{
    class X11OpenGLWindow
        : public X11Window
    {
    public:
        static inline std::vector<GLint> DEFAULT_DOUBLEBUFFER_VISUAL_ATTRIBUTES = {
            GLX_X_RENDERABLE, True,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_ALPHA_SIZE, 8,
            GLX_DEPTH_SIZE, 24,
            GLX_STENCIL_SIZE, 8,
            GLX_DOUBLEBUFFER, True,
            None
        };

        static inline std::vector<GLint> DEFAULT_SINGLEBUFFER_VISUAL_ATTRIBUTES = {
            GLX_X_RENDERABLE, True,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_ALPHA_SIZE, 8,
            GLX_DEPTH_SIZE, 24,
            GLX_STENCIL_SIZE, 8,
            GLX_DOUBLEBUFFER, False,
            None
        };

    public:
        X11OpenGLWindow(int _width, int _height, const std::string& _title = "undefined",
            const std::vector<GLint> _visualAttribs = DEFAULT_DOUBLEBUFFER_VISUAL_ATTRIBUTES);
        X11OpenGLWindow(int _x, int _y, int _width, int _height, const std::string& _title = "undefined",
            const std::vector<GLint> _visualAttribs = DEFAULT_DOUBLEBUFFER_VISUAL_ATTRIBUTES);
        ~X11OpenGLWindow();

        void initialize() override;
        void nextEvent() override;
        void update() override;
        void updateSingle();

    private:
        void initializeContext();
        void onWindowResize();

        GLXContext context_;
        std::vector<GLint> visualAttribs_;
        bool grabbed;
    };
}

#endif // NAGE_ENGINE_IO_X11OPENGLWINDOW_H_
