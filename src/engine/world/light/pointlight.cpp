#include "engine/render/glrenderengine.h"
#include "pointlight.h"

namespace NAGE
{
    PointLight::PointLight()
        : mId(-1),
          mShader(nullptr),
          mTransform(new Transform),
          mAttenuation(Vector3f(1.0f, 0.0f, 0.0f))
    {

    }

    PointLight::PointLight(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices)
        : IObject(_vertices, _indices),
          mId(-1),
          mShader(nullptr),
          mTransform(new Transform),
          mAttenuation(Vector3f(1.0f, 0.0f, 0.0f))
    {
        setupBuffer();
    }

    PointLight::~PointLight()
    {
        delete mShader;
        delete mTransform;
    }

    int PointLight::id() const
    {
        return mId;
    }

    Shader* PointLight::shader()
    {
        return mShader;
    }

    Transform* PointLight::transform()
    {
        return mTransform;
    }

    Vector3f PointLight::attenuation() const
    {
        return mAttenuation;
    }

    void PointLight::setId(int _id)
    {
        mId = _id;
    }

    void PointLight::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void PointLight::setTransformation(Transform* _transform)
    {
        mTransform = _transform;
    }

    void PointLight::setAttenuation(const Vector3f& _attenuation)
    {
        mAttenuation = _attenuation;
    }

    void PointLight::setAttenuation(float _x, float _y, float _z)
    {
        mAttenuation = Vector3f(_x, _y, _z);
    }

    void PointLight::use(Camera* _camera, Shader* _shader)
    {
        // Check if id was specified.
        if(mId <= -1)
            return;

        _shader->use();
        _shader->setVec3("cameraPosition", _camera->translation());
        _shader->setVec3("pointLights[" + std::to_string(mId) + "].position", mTransform->translation());
        _shader->setVec3("pointLights[" + std::to_string(mId) + "].color", mColor.red(), mColor.green(),
            mColor.blue());
        _shader->setVec3("pointLights[" + std::to_string(mId) + "].attenuation", mAttenuation);
    }

    void PointLight::draw(Camera* _camera)
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

        // Draw mesh.
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
