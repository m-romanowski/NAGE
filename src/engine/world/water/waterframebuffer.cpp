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
        return this->mBufferTexture->id();
    }

    void WaterFrameBuffer::initializeFrameBufferTexture()
    {
        // Frame buffer should be created here.

        // Create frame buffer texture.
        mBufferTexture = std::make_shared<Texture>(TextureType::TEXTURE_2D);
        mBufferTexture->empty(this->mWidth, this->mHeight); // Create empty 2D texture

        // Attach texture to frame buffer.
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mBufferTexture->id(), 0);
    }
}
