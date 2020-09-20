#ifndef NAGE_ENGINE_WORLD_WATER_WATERFRAMEBUFFER_H_
#define NAGE_ENGINE_WORLD_WATER_WATERFRAMEBUFFER_H_

#include "engine/render/framebuffer.h"
#include "engine/render/texture.h"

#include <memory>

namespace NAGE
{
    class WaterFrameBuffer : public FrameBuffer
    {
    public:
        WaterFrameBuffer(const GLint _width, const GLint _height);

        // Getters
        GLuint textureId() const;

    protected:
        virtual void setup() = 0;

    private:
        void initializeFrameBufferTexture();

        std::shared_ptr<Texture> bufferTexture_;
    };
}

#endif // NAGE_ENGINE_WORLD_WATER_WATERFRAMEBUFFER_H_
