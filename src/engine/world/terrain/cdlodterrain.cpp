#include "engine/render/glrenderengine.h"
#include "cdlodterrain.h"

namespace mr::nage
{
    CDLODTerrain::CDLODTerrain(const std::string& _id, int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : ICDLODObject(_lodLevel, _heightmap, _settings),
          ITerrain(_id)
    {
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "src/engine/shader/cdlodterrain2.vert");
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "src/engine/shader/cdlodterrain2.frag");
        shader_->link();

        material_->setAmbient(Vector3f(0.2f, 0.2f, 0.2f));
        material_->setDiffuse(Vector3f(0.5f, 0.5f, 0.5f));
        material_->setSpecular(Vector3f(0.05f, 0.05f, 0.05f));
        material_->setShininess(32.0f);
    }

    CDLODTerrain::~CDLODTerrain()
    {

    }

    void CDLODTerrain::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        // Heightmap
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, heightMap_->textureId());

        shader_->use();
        shader_->setVec4("clipPlane", _clipPlane.x(), _clipPlane.y(), _clipPlane.z(), _clipPlane.w());

        renderCDLOD(_camera, shader_, transform_);
    }
}
