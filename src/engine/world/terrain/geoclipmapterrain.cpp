#include "engine/render/glrenderengine.h"
#include "geoclipmapterrain.h"

namespace mr::nage
{
    GeoClipMapTerrain::GeoClipMapTerrain(const std::string& _id, HeightMap* _heightMap, const float _maxHeight, const unsigned int _levels)
        : GeoClipMapLOD(_levels, _heightMap, _maxHeight),
          ITerrain(_id)
    {
        Shader* shader = resource_->shader();
        shader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "src/engine/shader/geoclipmap.vert");
        shader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "src/engine/shader/geoclipmap.frag");
        shader->link();

        material_->setAmbient(Vector3f(0.2f, 0.2f, 0.2f));
        material_->setDiffuse(Vector3f(0.5f, 0.5f, 0.5f));
        material_->setSpecular(Vector3f(0.005f, 0.005f, 0.005f));
        material_->setShininess(0.5f);
    }

    GeoClipMapTerrain::~GeoClipMapTerrain()
    {

    }

    void GeoClipMapTerrain::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        Shader* shader = resource_->shader();
        shader->use();
        shader->setVec4("clipPlane", _clipPlane.x(), _clipPlane.y(), _clipPlane.z(), _clipPlane.w());

        // We need transpose matrix for OpenGL (matrix column major).
        shader->use();
        shader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        shader->setMat4("view", _camera->view().transpose());
        shader->setMat4("model", transform_->model().transpose());

       renderLOD(_camera, shader, transform_);
    }
}
