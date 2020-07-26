#include "engine/render/glrenderengine.h"
#include "cdlodterrain.h"

namespace NAGE
{
    CDLODTerrain::CDLODTerrain(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settings)
        : ICDLODObject(_lodLevel, _heightmap, _settings)
    {
        mShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/cdlodterrain2.vert");
        mShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/cdlodterrain2.frag");
        mShader->link();

        mMaterial->setAmbient(Vector3f(0.2f, 0.2f, 0.2f));
        mMaterial->setDiffuse(Vector3f(0.5f, 0.5f, 0.5f));
        mMaterial->setSpecular(Vector3f(0.05f, 0.05f, 0.05f));
        mMaterial->setShininess(32.0f);
    }

    CDLODTerrain::~CDLODTerrain()
    {

    }

    void CDLODTerrain::render(Camera* _camera, Vector4f _clipPlane)
    {
        // Heightmap
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mHeightMap->textureId());

        mShader->use();
        mShader->setVec4("clipPlane", _clipPlane.x(), _clipPlane.y(), _clipPlane.z(), _clipPlane.w());

        renderCDLOD(_camera, mShader, mTransform);
    }
}
