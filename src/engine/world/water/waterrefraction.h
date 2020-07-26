#ifndef NAGE_ENGINE_WORLD_WATER_WATERREFRACTION_H_
#define NAGE_ENGINE_WORLD_WATER_WATERREFRACTION_H_

#include "waterframebuffer.h"

namespace NAGE
{
    class WaterRefraction : public WaterFrameBuffer
    {
    public:
        WaterRefraction(int _width, int _height);

        // Getters
        GLuint depthTextureId();

        void setup() override;

    private:
        std::shared_ptr<Texture> mDepthTexture;
    };
}

#endif // NAGE_ENGINE_WORLD_WATER_WATERREFRACTION_H_
