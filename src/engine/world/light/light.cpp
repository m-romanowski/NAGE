#include "engine/render/glrenderengine.h"
#include "light.h"

namespace NAGE
{
    Light::Light()
        : color_(Color(1.0f, 1.0f, 1.0f))
    {

    }

    Color Light::color() const
    {
        return color_;
    }

    void Light::setColor(const Color& _color)
    {
        color_ = _color;
    }
}
