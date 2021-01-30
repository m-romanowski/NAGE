#ifndef NAGE_ENGINE_RENDER_SKYBOX_DAYNIGHTSKYDOME_H_
#define NAGE_ENGINE_RENDER_SKYBOX_DAYNIGHTSKYDOME_H_

#include "engine/render/renderableobject.h"
#include "engine/world/primitives/sphere.h"
#include "sunlight.h"

#include <string>

namespace mr::nage
{
    class DayNightSkydome
        : public Sphere
    {
    public:
        DayNightSkydome(const std::string& _id, Shader* _shader, SunLight* _sun, float _radius);

        void draw(Camera* _camera, const Vector4f _clipPlane) override;
        int depth() const override;

    private:
        float atmosphereRadius_;
        SunLight* sun_;
    };
}

#endif // NAGE_ENGINE_RENDER_SKYBOX_DAYNIGHTSKYDOME_H_
