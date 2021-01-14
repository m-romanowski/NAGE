#include "engine/render/vertexhelper.h"
#include "geoclipmapdegeneratetriangle.h"

namespace mr::nage
{
    GeoClipMapDegenrateTriangle::GeoClipMapDegenrateTriangle(const float _gridSpacing, unsigned int _gridSize)
        : gridSpacing_(_gridSpacing)
    {
        create(_gridSize);
    }

    void GeoClipMapDegenrateTriangle::create(unsigned int _gridSize)
    {
        setupVertices(_gridSize);
        setupIndices(_gridSize);
        VertexHelper::calculateNormals(vertices_, indices_);
        setupBuffer();
    }

    void GeoClipMapDegenrateTriangle::setupVertices(unsigned int _gridSize)
    {
        for(unsigned int z = 0; z < _gridSize; z++)
        {
            for(unsigned int x = 0; x < _gridSize; x++)
                vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        for(unsigned int z = 0; z < _gridSize; z++)
        {
            for(unsigned int x = 0; x < _gridSize; x++)
                vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        for(unsigned int z = 0; z < _gridSize; z++)
        {
            for(unsigned int x = _gridSize - 1; x < (_gridSize * 2) - 1; x++)
                vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        for(unsigned int z = _gridSize - 1; z < (_gridSize * 2) - 1; z++)
        {
            for(unsigned int x = 0; x < _gridSize; x++)
                vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }
    }

    void GeoClipMapDegenrateTriangle::setupIndices(unsigned int _gridSize)
    {
        unsigned int index = 0;
        indices_.resize(_gridSize * _gridSize * 6);

        // Right
        for(unsigned int z = 0; z < _gridSize - 1; z++)
        {
            for(unsigned int x = 0; x < 1; x++)
            {
                unsigned int offset = z * _gridSize + x;

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _gridSize;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _gridSize + 1;
                indices_[index + 5] = offset + _gridSize;

                index += 6;
            }
        }

        // Bottom
        for(unsigned int z = 0; z < 1; z++)
        {
            for(unsigned int x = 0; x < _gridSize - 1; x++)
            {
                unsigned int offset = z * _gridSize + x;

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _gridSize;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _gridSize + 1;
                indices_[index + 5] = offset + _gridSize;

                index += 6;
            }
        }

        // Left
        // TODO: fix
        for(unsigned int z = 0; z < _gridSize - 1; z++)
        {
            for(unsigned int x = 0; x < 1; x++)
            {
                unsigned int offset = ((z * _gridSize) + x + (2 * _gridSize)) - 2;

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _gridSize;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _gridSize + 1;
                indices_[index + 5] = offset + _gridSize;

                index += 6;
            }
        }

        // Top
        for(unsigned int z = 0; z < 1; z++)
        {
            for(unsigned int x = 0; x < _gridSize - 1; x++)
            {
                unsigned int offset = ((z * _gridSize) + x + (_gridSize * 3 * _gridSize));

                indices_[index] = offset;
                indices_[index + 1] = offset + 1;
                indices_[index + 2] = offset + _gridSize;
                indices_[index + 3] = offset + 1;
                indices_[index + 4] = offset + _gridSize + 1;
                indices_[index + 5] = offset + _gridSize;

                index += 6;
            }
        }
    }

    void GeoClipMapDegenrateTriangle::drawChunk(Shader* _shader, const Vector2f _levelPosition)
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
