#include "engine/render/glrenderengine.h"
#include "terrain.h"
#include "terrainchunk.h"

namespace NAGE
{
    TerrainChunk::TerrainChunk(Terrain* _terrain, float _x, float _z, int _width, int _height)
        : mPosition(Vector2f(_x, _z)),
          mWidth(_width),
          mHeight(_height)
    {
        terrain = _terrain;
        setupChunk(_x, _z, _width, _height);
    }

    TerrainChunk::TerrainChunk(Terrain* _terrain, const Vector2f& _position, int _width, int _height)
        : mPosition(_position),
          mWidth(_width),
          mHeight(_height)
    {
        terrain = _terrain;
        setupChunk(_position.x(), _position.y(), _width, _height);
    }

    void TerrainChunk::setupChunk(int _x, int _z, int _width, int _height)
    {
        mIndices.resize(_width * _height * 6);

        // Generate vertices.
        for (int x = _x; x < _x + _height; x++)
        {
            for (int z = _z; z < _z + _width; z++)
            {
                mVertices.push_back(Vertex(
                    Vector3f(static_cast<float>(x), 0.0f, static_cast<float>(z)),
                    Vector2f(static_cast<float>(z) / _width, static_cast<float>(x) / _height)
                ));
            }
        }

        // Generate indices.
        unsigned int index = 0;
        for (int x = 0; x < _height - 1; x++)
        {
            for (int z = 0; z < _height - 1; z++)
            {
                unsigned int offset = x * _height + z;

                mIndices[index] = offset;
                mIndices[index + 1] = offset + 1;
                mIndices[index + 2] = offset + _height;
                mIndices[index + 3] = offset + 1;
                mIndices[index + 4] = offset + _height + 1;
                mIndices[index + 5] = offset + _height;

                index += 6;
            }
        }

        // Calculate normals and setup (VAO, ...) buffers.
        Primitive::calculateNormals(mVertices, mIndices);
        setupBuffer();
    }

    float TerrainChunk::x() const
    {
        return mPosition.x();
    }

    float TerrainChunk::z() const
    {
        return mPosition.y();
    }

    Vector2f TerrainChunk::position() const
    {
        return mPosition;
    }

    int TerrainChunk::width() const
    {
        return mWidth;
    }

    int TerrainChunk::height() const
    {
        return mHeight;
    }

    bool TerrainChunk::isVisible() const
    {
        return mVisible;
    }

    void TerrainChunk::setVisible(bool _visible)
    {
        mVisible = _visible;
    }

    void TerrainChunk::draw(Camera* _camera, Shader* _shader)
    {
        if(!_shader)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::error(code.message());

            return;
        }

        // We need transpose matrix for OpenGL (matrix column major).
        _shader->use();
        _shader->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        _shader->setMat4("view", _camera->view().transpose());
        _shader->setMat4("model", terrain->transform()->model().transpose()); // I took transform matrix from the terrain class (transformation is for each chunk).

        // Draw mesh.
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
