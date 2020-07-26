#include "iwater.h"

#include <climits>
#include <random>

namespace NAGE
{
    IWater::IWater()
        : mShader(new Shader),
          mTransform(new Transform),
          mWaveMoveOffsetSpeed(0.0005)
    {
        mWaterReflection = std::make_shared<WaterReflection>(1024, 768);
        mWaterRefraction = std::make_shared<WaterRefraction>(640, 480);
        //mFlowMap = std::make_unique<FlowMap>();

        mFlowMapTexture = std::make_unique<Texture>("../resources/texture/water/flowmap.png", TextureType::TEXTURE_2D);
    }

    IWater::~IWater()
    {
        delete mShader;
        delete mTransform;
    }

    Shader* IWater::shader()
    {
        return mShader;
    }

    Transform* IWater::transform()
    {
        return mTransform;
    }

    std::shared_ptr<WaterReflection> IWater::waterReflectionEffect() const
    {
        return this->mWaterReflection;
    }

    std::shared_ptr<WaterRefraction> IWater::waterRefractionEffect() const
    {
        return this->mWaterRefraction;
    }

    void IWater::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void IWater::setTransformation(Transform* _transform)
    {
        mTransform = _transform;
    }

    void IWater::setWaveNoiseFactor(float _waveNoiseFactor)
    {
        mWaveNoiseFactor = _waveNoiseFactor;
    }

    void IWater::setWaveFrequency(float _waveFrequency)
    {
        mWaveFrequency = _waveFrequency;
    }

    void IWater::setWaveMoveOffsetSpeed(float _waveMoveOffsetSpeed)
    {
        mWaveMoveOffsetSpeed = _waveMoveOffsetSpeed;
    }

    void IWater::bindTextures()
    {
        // Bind reflection texture.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mWaterReflection->textureId());

        // Bind refraction texture.
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mWaterRefraction->textureId());

        // Bind flow map texture.
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, mFlowMapTexture->id());
        //glBindTexture(GL_TEXTURE_2D, mFlowMap->textureId());
    }

    void IWater::unbindTextures()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void IWater::setupWaterEffects()
    {
        mWaterReflection->setup();
        mWaterRefraction->setup();
    }

    void IWater::setupFlowMapEffect(int _width, int _height, int _seed)
    {
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
