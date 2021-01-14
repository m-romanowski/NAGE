#ifndef NAGE_ENGINE_WORLD_LIGHT_DIRECTIONALLIGHT_H_
#define NAGE_ENGINE_WORLD_LIGHT_DIRECTIONALLIGHT_H_

#include "ilight.h"

namespace mr::nage
{
    class DirectionalLight
        : public ILight
    {
    public:
        DirectionalLight();
        ~DirectionalLight() override;

        // Getters
        Vector3f lightDirection() const;
        LightType lightType() const override;

        // Setters
        void setLightDirection(const Vector3f& _direction);
        void setLightDirection(float _x, float _y, float _z);

        void use(Camera* _camera, Shader* _shader) override;

    protected:
        Vector3f lightDirection_;
    };
}

#endif // NAGE_ENGINE_WORLD_LIGHT_DIRECTIONALLIGHT_H_
