#ifndef NAGE_ENGINE_RENDER_FRAMEBUFFER_H_
#define NAGE_ENGINE_RENDER_FRAMEBUFFER_H_

#include "glad/glad.h"
#include "engine/io/iwindow.h"

#include <cassert>

namespace mr::nage
{
    class FrameBuffer
    {
    public:
        FrameBuffer(const GLint _width = 800, const GLint _height = 600);
        virtual ~FrameBuffer();

        // Getters
        GLuint frameBufferId() const;
        GLint width() const;
        GLint height() const;

        // Setters
        void setWidth(const GLint _width);
        void setHeight(const GLint _height);

        void bind();
        static void unbind(IWindow* _window, GLuint _frameBufferId = 0);

    protected:
        /**
         * @brief
         * Creates a new frame buffer.
         *
         * @return - frame buffer identificator
         */
        GLuint create();

        GLuint frameBufferId_;
        GLint width_, height_;
    };
}

#endif // NAGE_ENGINE_RENDER_FRAMEBUFFER_H_
