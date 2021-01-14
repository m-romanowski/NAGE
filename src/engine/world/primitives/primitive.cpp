#include "engine/render/glrenderengine.h"
#include "primitive.h"

namespace mr::nage
{
    Primitive::Primitive(const std::string& _id)
        : id_(_id),
          shader_(new Shader),
          transform_(new Transform)
    {

    }

    Primitive::~Primitive()
    {
        delete shader_;
        delete transform_;
    }

    std::string Primitive::id() const
    {
        return id_;
    }

    Shader* Primitive::shader()
    {
        return shader_;
    }

    Transform* Primitive::transformation()
    {
        return transform_;
    }

    unsigned long Primitive::verticesCount() const
    {
        return vertices_.size();
    }

    unsigned long Primitive::indicesCount() const
    {
        return indices_.size();
    }

    void Primitive::setShader(Shader* _shader)
    {
        shader_ = _shader;
    }

    void Primitive::setTransform(Transform* _transform)
    {
        transform_ = _transform;
    }

    void Primitive::initialize()
    {
        // Add default primitive shader (MVP and white color).
        shader_->addShaderFromSourceCode(SHADER_TYPE::SHADER_VERTEX,
            "#version 450 core\n"
            "layout (location = 0) in vec3 position;\n"
            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"
            "void main() {\n"
            "gl_Position = projection * view * model * vec4(position, 1.0f);\n"
            "}\n\0");

        shader_->addShaderFromSourceCode(SHADER_TYPE::SHADER_FRAGMENT,
            "#version 450 core\n"
            "out vec4 fragColor;\n"
            "void main() {\n"
            "fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
            "}\n\0");

        shader_->link();
    }

    void Primitive::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        NAGE_UNUSED(_clipPlane);

        if(!shader_)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // We need transpose matrix for OpenGL (matrix column major).
        shader_->use();
        shader_->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        shader_->setMat4("view", _camera->view().transpose());
        shader_->setMat4("model", transform_->model().transpose());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
