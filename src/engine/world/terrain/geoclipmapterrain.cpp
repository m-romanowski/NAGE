#include "engine/render/glrenderengine.h"
#include "geoclipmapterrain.h"

namespace mr::nage
{
    GeoClipMapTerrain::GeoClipMapTerrain(const std::string& _id, HeightMap* _heightMap, const float _maxHeight, const unsigned int _levels)
        : GeoClipMapLOD(_levels, _heightMap, _maxHeight),
          ITerrain(_id)
    {
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/geoclipmap.vert");
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/geoclipmap.frag");
        shader_->link();

        material_->setAmbient(Vector3f(0.2f, 0.2f, 0.2f));
        material_->setDiffuse(Vector3f(0.5f, 0.5f, 0.5f));
        material_->setSpecular(Vector3f(0.05f, 0.05f, 0.05f));
        material_->setShininess(1.0f);
    }

    GeoClipMapTerrain::~GeoClipMapTerrain()
    {

    }

    void GeoClipMapTerrain::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        shader_->use();
        shader_->setVec4("clipPlane", _clipPlane.x(), _clipPlane.y(), _clipPlane.z(), _clipPlane.w());

        // We need transpose matrix for OpenGL (matrix column major).
        shader_->use();
        shader_->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        shader_->setMat4("view", _camera->view().transpose());
        shader_->setMat4("model", transform_->model().transpose());

       renderLOD(_camera,shader_, transform_);
    }
}
