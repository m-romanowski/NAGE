#ifndef NAGE_ENGINE_RENDER_DIRECTIONALLIGHT_LIGHT_H_
#define NAGE_ENGINE_RENDER_DIRECTIONALLIGHT_LIGHT_H_

#include "ilight.h"

namespace mr::nage
{
    class DirectionalLight : public ILight
    {
    public:
        DirectionalLight();
        ~DirectionalLight() override;

        // Getters
        Vector3f lightDirection() const;

        // Setters
        void setLightDirection(const Vector3f& _direction);
        void setLightDirection(float _x, float _y, float _z);

        void use(Camera* _camera, Shader* _shader) override;

    protected:
        Vector3f lightDirection_;
    };
}

#endif // NAGE_ENGINE_RENDER_DIRECTIONALLIGHT_LIGHT_H_
