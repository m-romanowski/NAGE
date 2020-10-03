#include "engine/render/glrenderengine.h"
#include "ilight.h"

namespace mr::nage
{
    ILight::ILight()
        : color_(Color(1.0f, 1.0f, 1.0f))
    {

    }

    Color ILight::color() const
    {
        return color_;
    }

    void ILight::setColor(const Color& _color)
    {
        color_ = _color;
    }
}
