#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_PLANE_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_PLANE_H_

#include "primitive.h"

namespace NAGE
{
    class Plane : public Primitive
    {
    public:
        Plane(int _width, int _height);

        void setupPrimitive() override;
        static void generateFlatPlane(int _width, int _height, std::vector<Vertex>& _vertices,
            std::vector<unsigned int>& _indices);

    protected:
        int mWidth, mHeight;
    };
}

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_PLANE_H_
