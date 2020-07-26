#include "waterrefraction.h"

namespace NAGE
{
    WaterRefraction::WaterRefraction(int _width, int _height)
        : WaterFrameBuffer(_width, _height)
    {

    }

    GLuint WaterRefraction::depthTextureId()
    {
        return mDepthTexture->id();
    }

    void WaterRefraction::setup()
    {
        // Create depth texture.
        mDepthTexture = std::make_shared<Texture>(TextureType::TEXTURE_2D);
        mDepthTexture->empty(this->mWidth, this->mHeight);

        // Attach depth texture.
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mDepthTexture->id(), 0);
    }
}
