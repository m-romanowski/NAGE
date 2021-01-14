#ifndef NAGE_ENGINE_WORLD_LIGHT_DIRECTIONALIGHTOBJECT_H_
#define NAGE_ENGINE_WORLD_LIGHT_DIRECTIONALIGHTOBJECT_H_

#include "directionallight.h"
#include "engine/render/renderableobject.h"

namespace mr::nage
{
    class DirectionalLightObject
        : public DirectionalLight,
          public RenderableObject
    {
    public:
        DirectionalLightObject(const std::string& _id);
        DirectionalLightObject(const std::string& _id, const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        ~DirectionalLightObject();

        // Getters
        Shader* shader() override;
        bool isLightSource() const override;
        Transform* transformation() override;

        // Setters
        void setShader(Shader* _shader);
        void setTransformation(Transform* _transform);
        void setGradientExpand(float _gradientExpand);

        std::string id() const override;
        void draw(Camera* _camera, const Vector4f _clipPlane) override;
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        std::string id_;
        Shader* shader_;
        Transform* transform_;
        float gradientExpand_;
    };
}

#endif // NAGE_ENGINE_WORLD_LIGHT_DIRECTIONALIGHTOBJECT_H_
