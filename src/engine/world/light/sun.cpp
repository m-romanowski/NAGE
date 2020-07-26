#include "engine/render/glrenderengine.h"
#include "sun.h"

namespace NAGE
{
    Sun::Sun()
        : mTransform(new Transform)
    {
        mVertices = vertices();
        mIndices = indices();

        setup();
        setupBuffer();
    }

    Sun::Sun(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
        : mTransform(new Transform)
    {
        setVertices(_vertices);
        setIndices(_indices);
        setup();
        setupBuffer();
    }

    Sun::~Sun()
    {
        delete mShader;
        delete mTransform;
    }

    Shader* Sun::shader()
    {
        return mShader;
    }

    Transform* Sun::transform()
    {
        return mTransform;
    }

    void Sun::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void Sun::setTransformation(Transform* _transform)
    {
        mTransform = _transform;
    }

    void Sun::setGradientExpand(float _gradientExpand)
    {
        mGradientExpand = _gradientExpand;
    }

    void Sun::setup()
    {
        // Shader
        mShader = new Shader;
        mShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/lamp.vert");
        mShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/lamp.frag");
        mShader->link();

        // Transformation
        mTransform->setTranslation(Vector3f(200.0f, 1000.0f, 140.0f));
        mTransform->setScale(30.0f);

        // Sun color
        mColor = Color(238, 220, 165);
    }

    void Sun::draw(Camera* _camera)
    {
        if(!mShader)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // Draw light object.
        mShader->use();
        mShader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        mShader->setMat4("view", _camera->view().transpose());
        mShader->setMat4("model", mTransform->model().transpose());
        mShader->setVec3("color", mColor.red(), mColor.green(), mColor.blue());
        mShader->setFloat("expand", mGradientExpand);
        mShader->setVec2("center", mTransform->translation().x(), mTransform->translation().y());
        mShader->setFloat("radius", radius());
        mShader->setFloat("windowHeight", IWindow::currentWindowSize().y());

        // Draw mesh.
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
