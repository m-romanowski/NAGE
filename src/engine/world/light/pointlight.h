#ifndef NAGE_ENGINE_RENDER_POINTLIGHT_LIGHT_H_
#define NAGE_ENGINE_RENDER_POINTLIGHT_LIGHT_H_

#include "light.h"
#include "engine/render/iobject.h"

namespace NAGE
{
    class PointLight : public Light, public IObject
    {
    public:
        PointLight();
        PointLight(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        ~PointLight() override;

        // Getters
        int id() const;
        Shader* shader();
        Transform* transform();
        Vector3f attenuation() const;

        // Setters
        void setId(int _id);
        void setShader(Shader* _shader);
        void setTransformation(Transform* _transform);
        void setAttenuation(float _x, float _y, float _z);
        void setAttenuation(const Vector3f& _attenuation);

        void draw(Camera* _camera) override;
        void use(Camera* _camera, Shader* _shader) override;

    protected:
        int id_;
        Shader* shader_;
        Transform* transform_;
        Vector3f attenuation_;
    };
}

#endif // NAGE_ENGINE_RENDER_POINTLIGHT_LIGHT_H_
