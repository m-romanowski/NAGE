#ifndef NAGE_ENGINE_RENDER_VERTEX_H_
#define NAGE_ENGINE_RENDER_VERTEX_H_

#include "engine/math/NAGEMath/nagemathvector.h"

namespace NAGE
{
    class Vertex
    {
    public:
        Vertex(
            const Vector3f _position = Vector3f(0.0f, 0.0f, 0.0f),
            const Vector2f _textureCoords = Vector2f(0.0f, 0.0f),
            const Vector3f _normal = Vector3f(0.0f, 0.0f, 0.0f),
            const Vector4f _color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f))
            : position_(_position),
              textureCoords_(_textureCoords),
              normal_(_normal),
              color_(_color)
        {

        }

        Vector3f position_;
        Vector2f textureCoords_;
        Vector3f normal_;
        Vector4f color_;
    };
}

#endif // NAGE_ENGINE_RENDER_VERTEX_H_
