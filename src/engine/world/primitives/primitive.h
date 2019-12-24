#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_PRIMITIVE_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_PRIMITIVE_H_

#include "engine/render/iobject.h"
#include <string>

namespace NAGE
{
    class Primitive : public IObject
    {
    public:
        Primitive();
        virtual ~Primitive() override;

        // Getters
        Shader* shader();
        Transform* transform();
        unsigned long verticesCount() const;
        unsigned long indicesCount() const;

        // Setters
        void setShader(Shader* _shader);
        void setTransform(Transform* _transform);

        // Setup primitve vertices and indices.
        void initialize();
        virtual void draw(Camera* _camera) override;
        static void calculateNormals(std::vector<Vertex>& _vertices,
            std::vector<unsigned int>& _indices);

    protected:
        virtual void setupPrimitive() = 0;

        Shader* mShader;
        Transform* mTransform;
        unsigned int mVerticesCount, mIndicesCount;
    };
}

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_PRIMITIVE_H_
