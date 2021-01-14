#include "engine/render/vertexhelper.h"
#include "geoclipmapringfixup.h"

namespace mr::nage
{
    GeoClipMapRingFixUp::GeoClipMapRingFixUp(const float _gridSpacing, const unsigned int _gridSize, const unsigned int n)
        : gridSpacing_(_gridSpacing)
    {
        create(_gridSize, n);
    }

    void GeoClipMapRingFixUp::create(unsigned int _gridSize, unsigned int _n)
    {
        setupVertices(_gridSize, _n);
        setupIndices(_n);
        VertexHelper::calculateNormals(vertices_, indices_);
        setupBuffer();
    }

    void GeoClipMapRingFixUp::setupVertices(unsigned int _gridSize, unsigned int _n)
    {
        unsigned int index = 0;
        vertices_.resize(_n * 3 * 4);

        // Right
        for(unsigned int z = (_n - 1) * 2; z < ((_n - 1) * 2) + 3; z++)
        {
            for(unsigned int x = 0; x < _n; x++)
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
        }

        // Left
        for(unsigned int z = (_n - 1) * 2; z < ((_n - 1) * 2) + 3; z++)
        {
            for(unsigned int x = (_gridSize - 1) - (_n - 1); x < _gridSize; x++)
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
        }

        // Top
        for(unsigned int z = 0; z < _n; z++)
        {
            for(unsigned int x = (_n * 2) - 2; x < ((_n * 2) + _n) - 2; x++)
                vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        // Bottom
        for(unsigned int z = (_gridSize - 1) - (_n - 1); z < _gridSize; z++)
        {
            for(unsigned int x = (_n * 2) - 2; x < ((_n * 2) + _n) - 2; x++)
                vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }
    }

    void GeoClipMapRingFixUp::setupIndices(unsigned int _n)
    {
        unsigned int index = 0;
        indices_.resize(4 * 12 * _n);

        // Right
        for(unsigned int z = 0; z < 2; z++)
        {
            for(unsigned int x = 0; x < _n - 1; x++)
            {
                unsigned int offset = z * _n + x;

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _n;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _n + 1;
                indices_[index + 5] = offset + _n;

                index += 6;
            }
        }

        // Left
        for(unsigned int z = 0; z < 2; z++)
        {
            for(unsigned int x = 0; x < _n - 1; x++)
            {
                unsigned int offset = ((z * _n) + x + (_n * 3));

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _n;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _n + 1;
                indices_[index + 5] = offset + _n;

                index += 6;
            }
        }

        // Bottom
        for (unsigned int z = 0; z < _n - 1; z++)
        {
            for (unsigned int x = 0; x < 2; x++)
            {
                unsigned int offset = ((z * _n) + x + (_n * 3 * 4));

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _n;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _n + 1;
                indices_[index + 5] = offset + _n;

                index += 6;
            }
        }

        // Top
        for (unsigned int z = 1; z < _n; z++)
        {
            for (unsigned int x = 0; x < 2; x++)
            {
                unsigned int offset = ((z * _n) + x + (_n * 3 * 25));

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _n;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _n + 1;
                indices_[index + 5] = offset + _n;

                index += 6;
            }
        }
    }

    void GeoClipMapRingFixUp::drawChunk(Shader* _shader, const Vector2f _levelPosition)
    {
        Vector4f scaleFactor = Vector4f(gridSpacing_, gridSpacing_, _levelPosition.x(), _levelPosition.y());

        _shader->use();
        _shader->setVec4("gmapping.scaleFactor", scaleFactor.x(), scaleFactor.y(), scaleFactor.z(), scaleFactor.w());
        _shader->setVec3("inColor", Vector3f(color.red(), color.green(), color.blue()));

        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
