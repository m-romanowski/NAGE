#ifndef NAGE_ENGINE_WORLD_WATER_IWATER_H_
#define NAGE_ENGINE_WORLD_WATER_IWATER_H_

#include "engine/render/renderableobject.h"
#include "engine/render/shader.h"
#include "engine/render/model/material.h"
#include "engine/render/transform.h"
#include "engine/render/texture.h"
#include "engine/components/camera/camera.h"
#include "engine/generators/flowmap.h"
#include "waterreflection.h"
#include "waterrefraction.h"

namespace mr::nage
{
    class IWater
        : public RenderableObject
    {
    public:
        IWater(const std::string& _id);
        virtual ~IWater();

        // Getters
        std::shared_ptr<WaterReflection> waterReflectionEffect() const;
        std::shared_ptr<WaterRefraction> waterRefractionEffect() const;
        Shader* shader() override;
        Transform* transformation() override;

        // Setters
        void setShader(Shader* _shader);
        void setTransformation(Transform* _transform);
        void setWaveNoiseFactor(float _waveNoiseFactor);
        void setWaveFrequency(float _waveFrequency);
        void setWaveMoveOffsetSpeed(float _waveMoveOffsetSpeed);

        void setupWaterEffects();
        void setupFlowMapEffect(int _width, int _height, int _seed = -1);

        std::string id() const override;
        bool isWaterSource() const override;
        void useMaterials() override {}
        virtual void bindTextures() override;
        virtual void unbindTextures() override;

    protected:
        std::string id_;
        Shader* shader_;
        Transform* transform_;
        std::shared_ptr<WaterReflection> waterReflection_;
        std::shared_ptr<WaterRefraction> waterRefraction_;
        // std::unique_ptr<FlowMap> mFlowMap;
        std::unique_ptr<Texture> flowMapTexture_;

        float waveNoiseFactor_, waveFrequency_;
        float waveMoveOffset_, waveMoveOffsetSpeed_;
    };
}

#endif // NAGE_ENGINE_WORLD_WATER_IWATER_H_
