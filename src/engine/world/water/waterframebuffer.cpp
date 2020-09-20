#include "waterframebuffer.h"

namespace NAGE
{
    WaterFrameBuffer::WaterFrameBuffer(const GLint _width, const GLint _height)
        : FrameBuffer(_width, _height)
    {
        assert(_width > 0 && _height > 0);
        initializeFrameBufferTexture();
    }

    GLuint WaterFrameBuffer::textureId() const
    {
        return this->bufferTexture_->id();
    }

    void WaterFrameBuffer::initializeFrameBufferTexture()
    {
        // Frame buffer should be created here.

        // Create frame buffer texture.
        bufferTexture_ = std::make_shared<Texture>(TextureType::TEXTURE_2D);
        bufferTexture_->empty(this->width_, this->height_); // Create empty 2D texture

        // Attach texture to frame buffer.
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, bufferTexture_->id(), 0);
    }
}
