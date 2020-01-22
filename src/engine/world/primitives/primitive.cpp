#include "engine/render/glrenderengine.h"
#include "primitive.h"

namespace NAGE
{
    Primitive::Primitive()
        : mShader(new Shader),
          mTransform(new Transform)
    {

    }

    Primitive::~Primitive()
    {
        delete mShader;
        delete mTransform;
    }

    Shader* Primitive::shader()
    {
        return mShader;
    }

    Transform* Primitive::transform()
    {
        return mTransform;
    }

    unsigned long Primitive::verticesCount() const
    {
        return mVertices.size();
    }

    unsigned long Primitive::indicesCount() const
    {
        return mIndices.size();
    }

    void Primitive::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void Primitive::setTransform(Transform* _transform)
    {
        mTransform = _transform;
    }

    void Primitive::initialize()
    {
        // Add default primitive shader (MVP and white color).
        mShader->addShaderFromSourceCode(SHADER_TYPE::SHADER_VERTEX,
            "#version 450 core\n"
            "layout (location = 0) in vec3 position;\n"
            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"
            "void main() {\n"
            "gl_Position = projection * view * model * vec4(position, 1.0f);\n"
            "}\n\0");

        mShader->addShaderFromSourceCode(SHADER_TYPE::SHADER_FRAGMENT,
            "#version 450 core\n"
            "out vec4 fragColor;\n"
            "void main() {\n"
            "fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
            "}\n\0");

        mShader->link();
    }

    void Primitive::draw(Camera* _camera)
    {
        if(!mShader)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // We need transpose matrix for OpenGL (matrix column major).
        mShader->use();
        mShader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        mShader->setMat4("view", _camera->view().transpose());
        mShader->setMat4("model", mTransform->model().transpose());

        // Draw mesh.
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
