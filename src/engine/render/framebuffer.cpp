#include "framebuffer.h"

namespace NAGE
{
    FrameBuffer::FrameBuffer(const GLint _width, const GLint _height)
        : frameBufferId_(create()),
          width_(_width),
          height_(_height)
    {

    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &this->frameBufferId_);
    }

    GLuint FrameBuffer::frameBufferId() const
    {
        return this->frameBufferId_;
    }

    GLint FrameBuffer::width() const
    {
        return this->width_;
    }

    GLint FrameBuffer::height() const
    {
        return this->height_;
    }

    void FrameBuffer::setWidth(const GLint _width)
    {
        assert(_width > 0);
        this->width_ = _width;
    }

    void FrameBuffer::setHeight(const GLint _height)
    {
        assert(_height > 0);
        this->height_ = _height;
    }

    void FrameBuffer::bind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferId_);
        glViewport(0, 0, this->width_, this->height_);
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
