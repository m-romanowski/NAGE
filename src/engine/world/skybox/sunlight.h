#ifndef NAGE_ENGINE_RENDER_SKYBOX_SUNLIGHT_H_
#define NAGE_ENGINE_RENDER_SKYBOX_SUNLIGHT_H_

#include "engine/world/primitives/sphere.h"
#include "engine/world/light/directionallightobject.h"

namespace mr::nage
{
    class SunLight
        : public DirectionalLightObject
    {
    public:
        SunLight();

        inline float radius() { return sphere.radius(); }

    private:
        static inline const Sphere sphere = Sphere("sun-sphere");
    };
}

#endif // NAGE_ENGINE_RENDER_SKYBOX_SUNLIGHT_H_
