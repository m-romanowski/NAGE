#include "waterreflection.h"

namespace mr::nage
{
    WaterReflection::WaterReflection(int _width, int _height)
        : WaterFrameBuffer(_width, _height)
    {

    }

    WaterReflection::~WaterReflection()
    {
        // Clean up.
        glDeleteRenderbuffers(1, &depthBuffer_);
    }

    void WaterReflection::setup()
    {
        // Create a new depth buffer.
        glGenRenderbuffers(1, &depthBuffer_);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->width_, this->height_);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER, depthBuffer_);
    }
}
