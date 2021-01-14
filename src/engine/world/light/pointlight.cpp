#include "pointlight.h"

namespace mr::nage
{
    PointLight::PointLight()
        : id_(-1),
          attenuation_(Vector3f(1.0f, 0.0f, 0.0f))
    {

    }

    int PointLight::id() const
    {
        return id_;
    }

    Vector3f PointLight::attenuation() const
    {
        return attenuation_;
    }

    ILight::LightType PointLight::lightType() const
    {
        return ILight::LightType::Point;
    }

    void PointLight::setId(int _id)
    {
        id_ = _id;
    }


    void PointLight::setAttenuation(const Vector3f& _attenuation)
    {
        attenuation_ = _attenuation;
    }

    void PointLight::setAttenuation(float _x, float _y, float _z)
    {
        setAttenuation(Vector3f(_x, _y, _z));
    }

    void PointLight::use(Camera* _camera, Shader* _shader, Transform* _transform)
    {
        // Check if id was specified.
        if(id_ <= -1)
            return;

        if(_shader)
        {
            _shader->use();
            _shader->setVec3("cameraPosition", _camera->translation());
            _shader->setVec3("pointLights[" + std::to_string(id_) + "].position", _transform->translation());
            _shader->setVec3("pointLights[" + std::to_string(id_) + "].color", color_.red(), color_.green(),
                color_.blue());
            _shader->setVec3("pointLights[" + std::to_string(id_) + "].attenuation", attenuation_);
        }
    }
}
