#include "cdlodwater.h"

using namespace std::chrono;

namespace NAGE
{
    CDLODWater::CDLODWater(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : ICDLODObject(_lodLevel, _heightmap, _settings)
    {
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/cdlodwater.vert");
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/cdlodwater.frag");
        shader_->link();
    }

    CDLODWater::~CDLODWater()
    {

    }

    void CDLODWater::render(Camera* _camera)
    {
        // Wave move offset speed must be independent of FPS (frames per second),
        waveMoveOffset_ += waveMoveOffsetSpeed_ * static_cast<float>(IWindow::deltaMs());
        waveMoveOffset_ = std::fmod(waveMoveOffset_, 1.0f);

        // Bind water effects.
        shader_->use();
        shader_->setInt("reflectionTexture", 0);
        shader_->setInt("refractionTexture", 1);
        shader_->setInt("flowMapTexture", 2);
        shader_->setFloat("waveNoiseFactor", waveNoiseFactor_);
        shader_->setFloat("waveFrequency", waveFrequency_);
        shader_->setFloat("waveMoveOffset", waveMoveOffset_);

        renderCDLOD(_camera, shader_, transform_);
    }
}
