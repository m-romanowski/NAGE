#ifndef NAGE_ENGINE_WORLD_LIGHT_POINTLIGHTOBJECT_H_
#define NAGE_ENGINE_WORLD_LIGHT_POINTLIGHTOBJECT_H_

#include "pointlight.h"
#include "engine/render/renderableobject.h"

namespace mr::nage
{
    class PointLightObject
        : public PointLight,
          public RenderableObject
    {
    public:
        PointLightObject(const std::string& _id);
        PointLightObject(const std::string& _id, const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        ~PointLightObject() override;

        // Getters
        Shader* shader() override;
        Transform* transformation() override;
        bool isLightSource() const override;
        Resource* resource() override { return nullptr; } // TODO

        // Setters
        void setShader(Shader* _shader);
        void setTransformation(Transform* _transform);

        std::string id() const override;
        void use(Camera* _camera, Shader* _shader) override;
        void draw(Camera* _camera, const Vector4f _clipPlane) override;
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        std::string id_;
        Shader* shader_;
        Transform* transform_;
    };
}

#endif // NAGE_ENGINE_WORLD_LIGHT_POINTLIGHTOBJECT_H_
