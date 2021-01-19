#include "cdlodwater.h"

using namespace std::chrono;

namespace mr::nage
{
    CDLODWater::CDLODWater(const std::string& _id, int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : ICDLODObject(_lodLevel, _heightmap, _settings),
          IWater(_id)
    {
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "src/engine/shader/cdlodwater.vert");
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "src/engine/shader/cdlodwater.frag");
        shader_->link();
    }

    CDLODWater::~CDLODWater()
    {

    }

    void CDLODWater::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        NAGE_UNUSED(_clipPlane);

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
