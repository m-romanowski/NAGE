#include "engine/render/glrenderengine.h"
#include "light.h"

namespace NAGE
{
    Light::Light()
        : mColor(Color(1.0f, 1.0f, 1.0f))
    {

    }

    Light::~Light()
    {

    }

    Color Light::color() const
    {
        return mColor;
    }

    void Light::setColor(const Color& _color)
    {
        mColor = _color;
    }
}
