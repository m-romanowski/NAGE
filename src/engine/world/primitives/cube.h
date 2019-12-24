#ifndef CUBE_H
#define CUBE_H

#include "primitive.h"

namespace NAGE
{
    class Cube : public Primitive
    {
    public:
        Cube();

        void setupPrimitive() override;
    };
}

#endif // CUBE_H
