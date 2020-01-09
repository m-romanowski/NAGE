#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_CUBE_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_CUBE_H_

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

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_CUBE_H_
