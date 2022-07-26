#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_SPHERE_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_SPHERE_H_

#include "primitive.h"

namespace mr::nage
{
    class Sphere
        : public Primitive
    {
    public:
        Sphere(const std::string& _id, unsigned int _sectorCount = 36, unsigned int _stackCount = 18, float _radius = 1.0f);

        // Getters
        unsigned int sectorCount() const;
        unsigned int stackCount() const;
        float radius() const;

        // Setters
        void setSectorCount(unsigned int _count);
        void setStackCount(unsigned int _count);
        void setRadius(float _radius);

        void setupPrimitive() override;
        static void generateSphere(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices,
            unsigned int _sectorCount = 36, unsigned int _stackCount = 18, float _radius = 1.0f);

    protected:
        unsigned int sectorCount_, stackCount_;
        float radius_;
    };
}

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_SPHERE_H_
