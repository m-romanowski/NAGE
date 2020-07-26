#ifndef NAGE_ENGINE_WORLD_WATER_IWATER_H_
#define NAGE_ENGINE_WORLD_WATER_IWATER_H_

#include "engine/render/shader.h"
#include "engine/render/model/material.h"
#include "engine/render/transform.h"
#include "engine/render/texture.h"
#include "engine/components/camera/camera.h"
#include "engine/generators/flowmap.h"
#include "waterreflection.h"
#include "waterrefraction.h"

namespace NAGE
{
    class IWater
    {
    public:
        IWater();
        virtual ~IWater();

        // Getters
        Shader* shader();
        Transform* transform();
        std::shared_ptr<WaterReflection> waterReflectionEffect() const;
        std::shared_ptr<WaterRefraction> waterRefractionEffect() const;

        // Setters
        void setShader(Shader* _shader);
        void setTransformation(Transform* _transform);
        void setWaveNoiseFactor(float _waveNoiseFactor);
        void setWaveFrequency(float _waveFrequency);
        void setWaveMoveOffsetSpeed(float _waveMoveOffsetSpeed);

        virtual void bindTextures();
        virtual void unbindTextures();
        virtual void render(Camera* _camera) = 0;
        void setupWaterEffects();
        void setupFlowMapEffect(int _width, int _height, int _seed = -1);

    protected:
        Shader* mShader;
        Transform* mTransform;
        std::shared_ptr<WaterReflection> mWaterReflection;
        std::shared_ptr<WaterRefraction> mWaterRefraction;
        // std::unique_ptr<FlowMap> mFlowMap;
        std::unique_ptr<Texture> mFlowMapTexture;

        float mWaveNoiseFactor, mWaveFrequency;
        float mWaveMoveOffset, mWaveMoveOffsetSpeed;
    };
}

#endif // NAGE_ENGINE_WORLD_WATER_IWATER_H_
