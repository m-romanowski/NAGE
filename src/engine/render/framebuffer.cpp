#include "framebuffer.h"

namespace NAGE
{
    FrameBuffer::FrameBuffer(const GLint _width, const GLint _height)
        : mFrameBufferId(create()),
          mWidth(_width),
          mHeight(_height)
    {

    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &this->mFrameBufferId);
    }

    GLuint FrameBuffer::frameBufferId() const
    {
        return this->mFrameBufferId;
    }

    GLint FrameBuffer::width() const
    {
        return this->mWidth;
    }

    GLint FrameBuffer::height() const
    {
        return this->mHeight;
    }

    void FrameBuffer::setWidth(const GLint _width)
    {
        assert(_width > 0);
        this->mWidth = _width;
    }

    void FrameBuffer::setHeight(const GLint _height)
    {
        assert(_height > 0);
        this->mHeight = _height;
    }

    void FrameBuffer::bind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, this->mFrameBufferId);
        glViewport(0, 0, this->mWidth, this->mHeight);
    }

    void FrameBuffer::unbind(IWindow* _window, GLuint _frameBufferId)
    {
        assert(_window != nullptr);

        glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
        glViewport(0, 0, _window->width(), _window->height());
    }

    GLuint FrameBuffer::create()
    {
        GLuint frameBufferId;

        glGenFramebuffers(1, &frameBufferId);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);

        return frameBufferId;
    }
}
