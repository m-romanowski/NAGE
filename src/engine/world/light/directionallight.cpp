#include "directionallight.h"

namespace mr::nage
{
    DirectionalLight::DirectionalLight()
    {

    }

    DirectionalLight::~DirectionalLight()
    {

    }

    Vector3f DirectionalLight::lightDirection() const
    {
        return lightDirection_;
    }

    void DirectionalLight::setLightDirection(const Vector3f& _direction)
    {
        lightDirection_ = _direction;
    }

    void DirectionalLight::setLightDirection(float _x, float _y, float _z)
    {
        lightDirection_ = Vector3f(_x, _y, _z);
    }

    void DirectionalLight::use(Camera* _camera, Shader* _shader)
    {
        _shader->use();
        _shader->setVec3("cameraPosition", _camera->translation());
        _shader->setVec3("directionalLight.direction", lightDirection_);
        _shader->setVec3("directionalLight.color", color_.red(), color_.green(), color_.blue());
    }
}
