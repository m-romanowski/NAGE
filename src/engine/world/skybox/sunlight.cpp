#include "engine/world/primitives/sphere.h"
#include "sunlight.h"

namespace mr::nage
{
    SunLight::SunLight()
        : DirectionalLightObject("Sun", sphere.vertices(), sphere.indices())
    {

    }
}
