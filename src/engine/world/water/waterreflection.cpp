#include "waterreflection.h"

namespace NAGE
{
    WaterReflection::WaterReflection(int _width, int _height)
        : WaterFrameBuffer(_width, _height)
    {

    }

    WaterReflection::~WaterReflection()
    {
        // Clean up.
        glDeleteRenderbuffers(1, &mDepthBuffer);
    }

    void WaterReflection::setup()
    {
        // Create a new depth buffer.
        glGenRenderbuffers(1, &mDepthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->mWidth, this->mHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER, mDepthBuffer);
    }
}
