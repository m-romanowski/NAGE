#ifndef NAGE_ENGINE_WORLD_WATER_WATERREFRACTION_H_
#define NAGE_ENGINE_WORLD_WATER_WATERREFRACTION_H_

#include "waterframebuffer.h"

namespace mr::nage
{
    class WaterRefraction : public WaterFrameBuffer
    {
    public:
        WaterRefraction(int _width, int _height);

        // Getters
        GLuint depthTextureId();

        void setup() override;

    private:
        std::shared_ptr<Texture> depthTexture_;
    };
}

#endif // NAGE_ENGINE_WORLD_WATER_WATERREFRACTION_H_
