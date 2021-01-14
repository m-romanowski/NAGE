#ifndef NAGE_ENGINE_WORLD_LIGHT_LIGHT_H_
#define NAGE_ENGINE_WORLD_LIGHT_LIGHT_H_

#include "engine/render/shader.h"
#include "engine/render/color.h"
#include "engine/components/camera/camera.h"
#include "engine/math/NAGEMath/nagemathvector.h"

namespace mr::nage
{
    /* Interface for the light types.
     */
    class ILight
    {
    public:
        enum class LightType
        {
            Point,
            Directional
        };

    public:
        ILight();
        virtual ~ILight() {}

        // Getters
        Color color() const;

        // Setters
        void setColor(const Color& _color);

        virtual void use(Camera* _camera, Shader* _shader) = 0;
        virtual LightType lightType() const = 0;

    protected:
        Color color_;
    };
}

#endif // NAGE_ENGINE_WORLD_LIGHT_LIGHT_H_
