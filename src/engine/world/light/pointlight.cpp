#include "engine/render/glrenderengine.h"
#include "pointlight.h"

namespace mr::nage
{
    PointLight::PointLight()
        : id_(-1),
          shader_(nullptr),
          transform_(new Transform),
          attenuation_(Vector3f(1.0f, 0.0f, 0.0f))
    {

    }

    PointLight::PointLight(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
        : IObject(_vertices, _indices),
          id_(-1),
          shader_(nullptr),
          transform_(new Transform),
          attenuation_(Vector3f(1.0f, 0.0f, 0.0f))
    {
        setupBuffer();
    }

    PointLight::~PointLight()
    {
        delete shader_;
        delete transform_;
    }

    int PointLight::id() const
    {
        return id_;
    }

    Shader* PointLight::shader()
    {
        return shader_;
    }

    Transform* PointLight::transform()
    {
        return transform_;
    }

    Vector3f PointLight::attenuation() const
    {
        return attenuation_;
    }

    void PointLight::setId(int _id)
    {
        id_ = _id;
    }

    void PointLight::setShader(Shader* _shader)
    {
        shader_ = _shader;
    }

    void PointLight::setTransformation(Transform* _transform)
    {
        transform_ = _transform;
    }

    void PointLight::setAttenuation(const Vector3f& _attenuation)
    {
        attenuation_ = _attenuation;
    }

    void PointLight::setAttenuation(float _x, float _y, float _z)
    {
        attenuation_ = Vector3f(_x, _y, _z);
    }

    void PointLight::use(Camera* _camera, Shader* _shader)
    {
        // Check if id was specified.
        if(id_ <= -1)
            return;

        _shader->use();
        _shader->setVec3("cameraPosition", _camera->translation());
        _shader->setVec3("pointLights[" + std::to_string(id_) + "].position", transform_->translation());
        _shader->setVec3("pointLights[" + std::to_string(id_) + "].color", color_.red(), color_.green(),
            color_.blue());
        _shader->setVec3("pointLights[" + std::to_string(id_) + "].attenuation", attenuation_);
    }

    void PointLight::draw(Camera* _camera)
    {
        if(!shader_)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // Draw light object.
        shader_->use();
        shader_->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        shader_->setMat4("view", _camera->view().transpose());
        shader_->setMat4("model", transform_->model().transpose());
        shader_->setVec3("color", color_.red(), color_.green(), color_.blue());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
