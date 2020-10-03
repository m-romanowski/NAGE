#include "waterrefraction.h"

namespace mr::nage
{
    WaterRefraction::WaterRefraction(int _width, int _height)
        : WaterFrameBuffer(_width, _height)
    {

    }

    GLuint WaterRefraction::depthTextureId()
    {
        return depthTexture_->id();
    }

    void WaterRefraction::setup()
    {
        // Create depth texture.
        depthTexture_ = std::make_shared<Texture>(TextureType::TEXTURE_2D);
        depthTexture_->empty(this->width_, this->height_);

        // Attach depth texture.
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture_->id(), 0);
    }
}
