#include "directionallight.h"

namespace NAGE
{
    DirectionalLight::DirectionalLight()
    {

    }

    DirectionalLight::~DirectionalLight()
    {

    }

    Vector3f DirectionalLight::lightDirection() const
    {
        return mLightDirection;
    }

    void DirectionalLight::setLightDirection(const Vector3f& _direction)
    {
        mLightDirection = _direction;
    }

    void DirectionalLight::setLightDirection(float _x, float _y, float _z)
    {
        mLightDirection = Vector3f(_x, _y, _z);
    }

    void DirectionalLight::use(Camera* _camera, Shader* _shader)
    {
        _shader->use();
        _shader->setVec3("cameraPosition", _camera->translation());
        _shader->setVec3("directionalLight.direction", mLightDirection);
        _shader->setVec3("directionalLight.color", mColor.red(), mColor.green(), mColor.blue());
    }
}
