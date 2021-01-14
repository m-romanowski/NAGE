#include "iwater.h"

#include <climits>
#include <random>

namespace mr::nage
{
    IWater::IWater(const std::string& _id)
        : id_(_id),
          shader_(new Shader),
          transform_(new Transform),
          waveMoveOffsetSpeed_(0.0005)
    {
        waterReflection_ = std::make_shared<WaterReflection>(1024, 768);
        waterRefraction_ = std::make_shared<WaterRefraction>(640, 480);
        // mFlowMap = std::make_unique<FlowMap>();

        flowMapTexture_ = std::make_unique<Texture>("../resources/texture/water/flowmap.png", TextureType::TEXTURE_2D);
    }

    IWater::~IWater()
    {
        delete shader_;
        delete transform_;
    }

    Shader* IWater::shader()
    {
        return shader_;
    }

    Transform* IWater::transformation()
    {
        return transform_;
    }

    std::shared_ptr<WaterReflection> IWater::waterReflectionEffect() const
    {
        return this->waterReflection_;
    }

    std::shared_ptr<WaterRefraction> IWater::waterRefractionEffect() const
    {
        return this->waterRefraction_;
    }

    void IWater::setShader(Shader* _shader)
    {
        shader_ = _shader;
    }

    void IWater::setTransformation(Transform* _transform)
    {
        transform_ = _transform;
    }

    void IWater::setWaveNoiseFactor(float _waveNoiseFactor)
    {
        waveNoiseFactor_ = _waveNoiseFactor;
    }

    void IWater::setWaveFrequency(float _waveFrequency)
    {
        waveFrequency_ = _waveFrequency;
    }

    void IWater::setWaveMoveOffsetSpeed(float _waveMoveOffsetSpeed)
    {
        waveMoveOffsetSpeed_ = _waveMoveOffsetSpeed;
    }

    void IWater::bindTextures()
    {
        // Bind reflection texture.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, waterReflection_->textureId());

        // Bind refraction texture.
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, waterRefraction_->textureId());

        // Bind flow map texture.
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, flowMapTexture_->id());
        //glBindTexture(GL_TEXTURE_2D, mFlowMap->textureId());
    }

    std::string IWater::id() const
    {
        return id_;
    }

    void IWater::unbindTextures()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void IWater::setupWaterEffects()
    {
        waterReflection_->setup();
        waterRefraction_->setup();
    }

    bool IWater::isWaterSource() const
    {
        return true;
    }

    void IWater::setupFlowMapEffect(int _width, int _height, int _seed)
    {
        NAGE_UNUSED(_width);
        NAGE_UNUSED(_height);

        // Generate random seed if was not defined.
        if(_seed == -1)
        {
            std::random_device randomDevice;
            std::default_random_engine randomEngine(randomDevice());
            std::uniform_int_distribution<unsigned long> uniform_dist(1, ULONG_MAX);

            _seed = uniform_dist(randomEngine);
        }

        // mFlowMap->generateTexture(_width, _height, _seed);
    }
}
