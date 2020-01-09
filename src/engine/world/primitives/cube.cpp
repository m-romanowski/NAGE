#include "cube.h"

namespace NAGE
{
    Cube::Cube()
    {
        mVertices = {
            Vertex(Vector3f(-1.0, -1.0,  1.0), Vector2f(0.0f, 0.0f)),
            Vertex(Vector3f(1.0, -1.0,  1.0), Vector2f(1.0f, 0.0f)),
            Vertex(Vector3f(1.0,  1.0,  1.0), Vector2f(1.0f, 1.0f)),
            Vertex(Vector3f(-1.0,  1.0,  1.0), Vector2f(0.0f, 1.0f)),

            Vertex(Vector3f(-1.0, -1.0, -1.0), Vector2f(0.0f, 0.0f)),
            Vertex(Vector3f(1.0, -1.0, -1.0), Vector2f(1.0f, 0.0f)),
            Vertex(Vector3f(1.0,  1.0, -1.0), Vector2f(1.0f, 1.0f)),
            Vertex(Vector3f(-1.0,  1.0, -1.0), Vector2f(0.0f, 1.0f)),
        };

        mIndices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
        };

        Primitive::calculateNormals(mVertices, mIndices);
    }

    void Cube::setupPrimitive()
    {
        setupBuffer();
    }
}
