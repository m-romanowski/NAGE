#include "engine/render/glrenderengine.h"
#include "pointlightobject.h"

namespace mr::nage
{
    PointLightObject::PointLightObject(const std::string& _id)
        : id_(_id),
          shader_(nullptr)
    {

    }

    PointLightObject::PointLightObject(const std::string& _id, const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
        : RenderableObject(_vertices, _indices),
          id_(_id),
          shader_(nullptr)
    {
        setupBuffer();
    }

    PointLightObject::~PointLightObject()
    {
        delete shader_;
        delete transform_;
    }

    std::string PointLightObject::id() const
    {
        return id_;
    }

    Shader* PointLightObject::shader()
    {
        return shader_;
    }

    Transform* PointLightObject::transformation()
    {
        return transform_;
    }

    bool PointLightObject::isLightSource() const
    {
        return true;
    }

    void PointLightObject::setShader(Shader* _shader)
    {
        shader_ = _shader;
    }

    void PointLightObject::setTransformation(Transform* _transform)
    {
        transform_ = _transform;
    }

    void PointLightObject::use(Camera* _camera, Shader* _shader)
    {
        PointLight::use(_camera, _shader, transform_);
    }

    void PointLightObject::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        NAGE_UNUSED(_clipPlane);

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
