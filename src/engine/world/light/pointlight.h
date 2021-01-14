#ifndef NAGE_ENGINE_WORLD_LIGHT_POINTLIGHT_H_
#define NAGE_ENGINE_WORLD_LIGHT_POINTLIGHT_H_

#include "engine/render/transform.h"
#include "ilight.h"

namespace mr::nage
{
    class PointLight
        : public ILight
    {
    public:
        PointLight();

        int id() const;
        Vector3f attenuation() const;
        LightType lightType() const override;

        // Setters
        void setId(int _id);
        void setAttenuation(float _x, float _y, float _z);
        void setAttenuation(const Vector3f& _attenuation);

        void use(Camera* _camera, Shader* _shader, Transform* _transform);

    protected:
        int id_;
        Vector3f attenuation_;
    };
}

#endif // NAGE_ENGINE_WORLD_LIGHT_POINTLIGHT_H_
