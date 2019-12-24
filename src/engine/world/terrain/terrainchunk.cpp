#include "engine/render/glrenderengine.h"
#include "terrain.h"
#include "terrainchunk.h"

namespace NAGE
{
    TerrainChunk::TerrainChunk(Terrain* _terrain, float _x, float _y, int _width, int _height)
        : mPosition(Vector2f(_x, _y)),
          mWidth(_width),
          mHeight(_height)
    {
        terrain = _terrain;

        float fWidth = static_cast<float>(_width);
        float fHeight = static_cast<float>(_height);

        mIndices.resize(_width * _height * 6);

        for(int x = _x; x < _x + _height; x++)
        {
            for(int z = _y; z < _y + _width; z++)
            {
                /*mVertices.push_back(Vertex(
                    Vector3f(static_cast<float>(x), _terrain->heightsv[x][z], static_cast<float>(z)),
                    Vector3f(0.0f, 0.0f, 0.0f),
                    Vector2f(static_cast<float>(z - _y) / fWidth, static_cast<float>(_x - x) / fHeight)
                ));*/
            }
        }

        unsigned int index = 0;
        for (unsigned int x = 0; x < _height - 1; x++)
        {
            for (unsigned int z = 0; z < _width - 1; z++)
            {
                unsigned int offset = x * _width + z;

                mIndices[index] = offset;
                mIndices[index + 1] = offset + 1;
                mIndices[index + 2] = offset + _width;
                mIndices[index + 3] = offset + 1;
                mIndices[index + 4] = offset + _width + 1;
                mIndices[index + 5] = offset + _width;

                index += 6;
            }
        }

        Primitive::calculateNormals(mVertices, mIndices);
        setupBuffer();
    }

    TerrainChunk::TerrainChunk(const Vector2f& _position, int _width, int _height)
        : mPosition(_position),
          mWidth(_width),
          mHeight(_height)
    {

    }

    float TerrainChunk::x() const
    {
        return mPosition.x();
    }

    float TerrainChunk::y() const
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
        _shader->setMat4("model", terrain->transform()->model().transpose());

        // Draw mesh.
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
    }
}
