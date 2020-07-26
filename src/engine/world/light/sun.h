#ifndef NAGE_ENGINE_RENDER_POINTLIGHT_SUN_H_
#define NAGE_ENGINE_RENDER_POINTLIGHT_SUN_H_

#include "directionallight.h"
#include "engine/render/iobject.h"
#include "engine/world/primitives/sphere.h"

namespace NAGE
{
    class Sun
        : public DirectionalLight, Sphere
    {
    public:
        Sun();
        Sun(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        ~Sun();

        // Getters
        Shader* shader();
        Transform* transform();

        // Setters
        void setShader(Shader* _shader);
        void setTransformation(Transform* _transform);
        void setGradientExpand(float _gradientExpand);

        void draw(Camera* _camera) override;

    private:
        void setup();

        Shader* mShader;
        Transform* mTransform;

        float mGradientExpand;
    };
}

#endif // NAGE_ENGINE_RENDER_POINTLIGHT_SUN_H_
