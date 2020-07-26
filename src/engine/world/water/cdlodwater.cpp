#include "cdlodwater.h"

using namespace std::chrono;

namespace NAGE
{
    CDLODWater::CDLODWater(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : ICDLODObject(_lodLevel, _heightmap, _settings)
    {
        mShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/cdlodwater.vert");
        mShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/cdlodwater.frag");
        mShader->link();
    }

    CDLODWater::~CDLODWater()
    {

    }

    void CDLODWater::render(Camera* _camera)
    {
        // Wave move offset speed must be independent of FPS (frames per second),
        mWaveMoveOffset += mWaveMoveOffsetSpeed * static_cast<float>(IWindow::deltaMs());
        mWaveMoveOffset = std::fmod(mWaveMoveOffset, 1.0f);

        // Bind water effects.
        mShader->use();
        mShader->setInt("reflectionTexture", 0);
        mShader->setInt("refractionTexture", 1);
        mShader->setInt("flowMapTexture", 2);
        mShader->setFloat("waveNoiseFactor", mWaveNoiseFactor);
        mShader->setFloat("waveFrequency", mWaveFrequency);
        mShader->setFloat("waveMoveOffset", mWaveMoveOffset);

        renderCDLOD(_camera, mShader, mTransform);
    }
}
