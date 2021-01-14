#include "engine/render/vertexhelper.h"
#include "geoclipmapinteriortrim.h"

namespace mr::nage
{
    GeoClipMapInteriorTrim::GeoClipMapInteriorTrim(const float _gridSpacing, unsigned int _gridSize, unsigned int n)
        : gridSpacing_(_gridSpacing)
    {
        create(_gridSize, n);
    }

    void GeoClipMapInteriorTrim::create(unsigned int _gridSize, unsigned int _n)
    {
        setupVertices(_gridSize, _n);
        setupIndices(_n);
        VertexHelper::calculateNormals(vertices_, indices_);
        setupBuffer();
    }

    void GeoClipMapInteriorTrim::setupVertices(unsigned int _gridSize, unsigned int _n)
    {
        unsigned int index = 0;
        vertices_.resize((_n * 8) + 2);

        // Top-left
        // Top
        for(unsigned int z = (_gridSize - _n - 1); z < _gridSize - (_n - 1); z++)
        {
            for(unsigned int x = _n - 1; x < _gridSize - (_n - 1); x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }

        // Left
        for(unsigned int z = _n - 1; z < (3 * _n) - 1; z++)
        {
            for(unsigned int x = _n - 1; x < _n + 1; x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }

        // Top-right
        index = 0;

        // Top
        for(unsigned int z = (_gridSize - _n - 1); z < _gridSize - (_n - 1); z++)
        {
            for(unsigned int x = _n - 1; x < _gridSize - (_n - 1); x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }

        // Right
        for(unsigned int z = _n - 1; z < (3 * _n) - 1; z++)
        {
            for(unsigned int x = _gridSize - (_n - 1); x < _gridSize - (_n - 1); x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }

        // Bottom-left
        index = 0;

        // Bottom
        for(unsigned int z = _n - 1; z < _n + 1; z++)
        {
            for(unsigned int x = _n - 1; x < _gridSize - (_n - 1); x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }

        // Left
        for(unsigned int z = _n; z < (3 * _n); z++)
        {
            for(unsigned int x = _n - 1; x < _n + 1; x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }

        // Bottom-right
        index = 0;

        // Bottom
        for(unsigned int z = _n - 1; z < _n + 1; z++)
        {
            for(unsigned int x = _n - 1; x < _gridSize - (_n - 1); x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }

        // Right
        for(unsigned int z = _n; z < 3 * _n; z++)
        {
            for(unsigned int x = _gridSize - (_n - 1); x < _gridSize - (_n - 1); x++)
            {
                vertices_[index++] = Vertex(Vector3f(x, 0.0f, z));
            }
        }
    }

    void GeoClipMapInteriorTrim::setupIndices(unsigned int _n)
    {
        unsigned int index = 0;
        indices_.resize((100 * _n) - 4);

        // Horizontal
        for(unsigned int z = 0; z < (2 * _n) + 1; z++)
        {
            indices_[index++] = z;
            indices_[index++] = (z + (2 * _n) + 1);

            // Last column.
            if(z == 2 * _n)
                indices_[index++] = (z + (2 * _n) + 1);
        }

        // Vertical
        for(unsigned int z = 0; z < (2 * _n) - 1; z++)
        {
            for(unsigned int x = 0; x < 2; x++)
            {
                // Degenerate triangle (left column).
                if(x == 0)
                    indices_[index++] = (z * 2) + (4 * _n) + 2 + x;

                indices_[index++] = (z * 2) + (4 * _n) + 2 + x;
                indices_[index++] = (z * 2) + (4 * _n) + 4 + x;

                // Degenerate triangle (right column).
                if(x == 1 && z < (2 * _n) - 2)
                    indices_[index++] = (z * 2) + (4 * _n) + 4 + x;
            }
        }
    }

    void GeoClipMapInteriorTrim::drawChunk(Shader* _shader, const Vector2f _levelPosition)
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
