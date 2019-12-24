#include "plane.h"

namespace NAGE
{
    Plane::Plane(int _width, int _height)
    {
        generateFlatPlane(_width, _height);
    }

    void Plane::setupPrimitive()
    {
        setupBuffer();
    }

    void Plane::generateFlatPlane(int _width, int _height)
    {
        unsigned int width = static_cast<unsigned int>(_width);
        unsigned int height = static_cast<unsigned int>(_height);
        float fWidth = static_cast<float>(width);
        float fHeight = static_cast<float>(height);

        mIndices.resize(width * height * 6);

        // Generate vertices.
        for (unsigned int x = 0; x < height; x++)
        {
            for (unsigned int z = 0; z < width; z++)
            {
                /* Perfect UV for a grid:
                 * u = (x + 0.5f) / height;
                 * v = (z + 0.5f) / widgth;
                 */

                // Push new Vertex(objectPosition, normals, textureCoords).
                mVertices.push_back(Vertex(
                    Vector3f(static_cast<float>(x), 0.0f, static_cast<float>(z)),
                    Vector3f(0.0f, 0.0f, 0.0f),
                    Vector2f(static_cast<float>(z + 0.5f) / fWidth, static_cast<float>(x + 0.5f) / fHeight)
                ));
            }
        }

        // Generate indices.
        unsigned int index = 0;
        for (unsigned int x = 0; x < height - 1; x++)
        {
            for (unsigned int z = 0; z < width - 1; z++)
            {
                unsigned int offset = x * width + z;

                mIndices[index] = offset;
                mIndices[index + 1] = offset + 1;
                mIndices[index + 2] = offset + width;
                mIndices[index + 3] = offset + 1;
                mIndices[index + 4] = offset + width + 1;
                mIndices[index + 5] = offset + width;

                index += 6;
            }
        }

        // Calculate normal vectors.
        Primitive::calculateNormals(mVertices, mIndices);
    }
}
