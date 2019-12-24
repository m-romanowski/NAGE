#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"

namespace NAGE
{
    class Plane : public Primitive
    {
    public:
        Plane(int _width, int _height);

        void setupPrimitive() override;

    private:
        void generateFlatPlane(int _width, int _height);

        int mWidth, mHeight;
    };
}

#endif // PLANE_H
