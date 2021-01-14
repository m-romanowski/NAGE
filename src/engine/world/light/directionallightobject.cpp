#include "engine/render/glrenderengine.h"
#include "directionallightobject.h"

namespace mr::nage
{
    DirectionalLightObject::DirectionalLightObject(const std::string& _id)
        : id_(_id),
          transform_(new Transform)
    {
        vertices_ = vertices();
        indices_ = indices();

        setupBuffer();
    }

    DirectionalLightObject::DirectionalLightObject(const std::string& _id, const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
        : id_(_id),
          transform_(new Transform)
    {
        setVertices(_vertices);
        setIndices(_indices);
        setupBuffer();
    }

    DirectionalLightObject::~DirectionalLightObject()
    {
        delete shader_;
        delete transform_;
    }

    std::string DirectionalLightObject::id() const
    {
        return id_;
    }

    Shader* DirectionalLightObject::shader()
    {
        return shader_;
    }

    Transform* DirectionalLightObject::transformation()
    {
        return transform_;
    }

    bool DirectionalLightObject::isLightSource() const
    {
        return true;
    }

    void DirectionalLightObject::setShader(Shader* _shader)
    {
        shader_ = _shader;
    }

    void DirectionalLightObject::setTransformation(Transform* _transform)
    {
        transform_ = _transform;
    }

    void DirectionalLightObject::setGradientExpand(float _gradientExpand)
    {
        gradientExpand_ = _gradientExpand;
    }

    void DirectionalLightObject::draw(Camera* _camera, const Vector4f _clipPlane)
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
        shader_->setFloat("expand", gradientExpand_);
        shader_->setVec2("center", transform_->translation().x(), transform_->translation().y());
        shader_->setFloat("windowHeight", IWindow::currentWindowSize().y());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
