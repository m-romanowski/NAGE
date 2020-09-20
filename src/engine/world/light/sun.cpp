#include "engine/render/glrenderengine.h"
#include "sun.h"

namespace NAGE
{
    Sun::Sun()
        : transform_(new Transform)
    {
        vertices_ = vertices();
        indices_ = indices();

        setup();
        setupBuffer();
    }

    Sun::Sun(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
        : transform_(new Transform)
    {
        setVertices(_vertices);
        setIndices(_indices);
        setup();
        setupBuffer();
    }

    Sun::~Sun()
    {
        delete shader_;
        delete transform_;
    }

    Shader* Sun::shader()
    {
        return shader_;
    }

    Transform* Sun::transform()
    {
        return transform_;
    }

    void Sun::setShader(Shader* _shader)
    {
        shader_ = _shader;
    }

    void Sun::setTransformation(Transform* _transform)
    {
        transform_ = _transform;
    }

    void Sun::setGradientExpand(float _gradientExpand)
    {
        gradientExpand_ = _gradientExpand;
    }

    void Sun::setup()
    {
        // Shader
        shader_ = new Shader;
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/lamp.vert");
        shader_->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/lamp.frag");
        shader_->link();

        // Transformation
        transform_->setTranslation(Vector3f(200.0f, 1000.0f, 140.0f));
        transform_->setScale(30.0f);

        // Sun color
        color_ = Color(238, 220, 165);
    }

    void Sun::draw(Camera* _camera)
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
        shader_->setFloat("expand", gradientExpand_);
        shader_->setVec2("center", transform_->translation().x(), transform_->translation().y());
        shader_->setFloat("radius", radius());
        shader_->setFloat("windowHeight", IWindow::currentWindowSize().y());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
