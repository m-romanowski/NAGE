#ifndef NAGE_ENGINE_WORLD_WATER_WATERREFLECTION_H_
#define NAGE_ENGINE_WORLD_WATER_WATERREFLECTION_H_

#include "waterframebuffer.h"

namespace NAGE
{
    class WaterReflection : public WaterFrameBuffer
    {
    public:
        WaterReflection(int _width, int _height);
        ~WaterReflection();

        void setup() override;

    private:
        GLuint mDepthBuffer;
    };
}

#endif // WATERREFLECTION_H
