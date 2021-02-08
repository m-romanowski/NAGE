#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_PRIMITIVE_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_PRIMITIVE_H_

#include "engine/render/renderableobject.h"
#include <string>

namespace mr::nage
{
    /* Primitive interface
     *
     * - basic shader
     * - basic transform
     */
    class Primitive
        : public RenderableObject
    {
    public:
        Primitive(const std::string& _id);
        virtual ~Primitive() override;

        // Getters
        unsigned long verticesCount() const;
        unsigned long indicesCount() const;
        Shader* shader() override;
        Transform* transformation() override;
        Resource* resource() override { return nullptr; } // TODO

        // Setters
        void setShader(Shader* _shader);
        void setTransform(Transform* _transform);

        // Setup primitve vertices and indices.
        void initialize();
        std::string id() const override;
        virtual void draw(Camera* _camera, const Vector4f _clipPlane) override;
        virtual void useMaterials() override {}
        virtual void bindTextures() override {}
        virtual void unbindTextures() override {}

    protected:
        virtual void setupPrimitive() = 0;

        std::string id_;
        Shader* shader_;
        Transform* transform_;
        unsigned int verticesCount_, indicesCount_;
    };
}

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_PRIMITIVE_H_
