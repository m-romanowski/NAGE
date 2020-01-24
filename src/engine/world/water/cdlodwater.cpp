#include "cdlodwater.h"
#include <chrono>

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

        mMaterial->setAmbient(Vector3f(0.2f, 0.2f, 0.2f));
        mMaterial->setDiffuse(Vector3f(0.5f, 0.5f, 0.5f));
        mMaterial->setSpecular(Vector3f(1.0f, 1.0f, 1.0f));
        mMaterial->setShininess(64.0f);
    }

    CDLODWater::~CDLODWater()
    {

    }

    void CDLODWater::render(Camera* _camera)
    {
        glDisable(GL_CULL_FACE);
        // If blending is enable remove "discard option" from fragment shader.
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //milliseconds ms = duration_cast< milliseconds >(
        //    system_clock::now().time_since_epoch()
        //);

        //mShader->use();
        //mShader->setFloat("deltaTime", ms.count());

        renderCDLOD(_camera, mShader, mTransform);

        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
}
