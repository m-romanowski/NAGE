#ifndef NAGE_ENGINE_RENDER_MODEL_MATERIAL_TYPE_H_
#define NAGE_ENGINE_RENDER_MODEL_MATERIAL_TYPE_H_

#include "material.h"

namespace NAGE
{
    //  Materials source: http://devernay.free.fr/cours/opengl/materials.html

    // Predefined material types.
    class MaterialType
    {
    public:
        const static Material DEFAULT;
        const static Material EMERALD;
        const static Material JADE;
        const static Material OBSIDIAN;
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_MATERIAL_TYPE_H_
