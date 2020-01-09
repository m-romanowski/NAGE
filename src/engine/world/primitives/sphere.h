#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_SPHERE_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_SPHERE_H_

#include "primitive.h"

namespace NAGE
{
    class Sphere : public Primitive
    {
    public:
        Sphere(unsigned int _sectorCount = 36, unsigned int _stackCount = 18, float _radius = 1.0f);

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

    private:
        unsigned int mSectorCount, mStackCount;
        float mRadius;
    };
}

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_SPHERE_H_
