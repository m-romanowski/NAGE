#include "cdlodobjectchunk.h"

namespace mr::nage
{
    CDLODObjectChunk::CDLODObjectChunk(int _size)
        : size_(_size)
    {
        setupMeshBuffers();
    }

    int CDLODObjectChunk::topLeftEndIndex() const
    {
        return topLeftEndIndex_;
    }

    int CDLODObjectChunk::topRightEndIndex() const
    {
        return topRightEndIndex_;
    }

    int CDLODObjectChunk::bottomLeftEndIndex() const
    {
        return bottomLeftEndIndex_;
    }

    int CDLODObjectChunk::bottomRightEndIndex() const
    {
        return bottomRightEndIndex_;
    }

    int CDLODObjectChunk::size() const
    {
        return size_;
    }

    void CDLODObjectChunk::appendIndices(int _x, int _z, int _size, int& _currentOffset)
    {
        indices_[_currentOffset++] = (_x + _size * _z);
        indices_[_currentOffset++] = ((_x + 1) + _size * _z);
        indices_[_currentOffset++] = ((_x + 1) + _size * (_z + 1));
        indices_[_currentOffset++] = ((_x + 1) + _size * (_z + 1));
        indices_[_currentOffset++] = (_x + _size * (_z + 1));
        indices_[_currentOffset++] = (_x + _size * _z);
    }

    void CDLODObjectChunk::setupMeshBuffers()
    {
        assert(size_ > 0);

        const int dim = size_ + 1;

        // Vertices
        for(int x = 0; x < dim; x++)
        {
            for(int z = 0; z < dim; z++)
            {
                float xx = (x - size_ / 2);
                float zz = (z - size_ / 2);
                xx = x;
                zz = z;

                vertices_.push_back(
                    Vertex(Vector3f(xx / size_, 0.0f, zz / size_))
                );
            }
        }

        // Indices
        indices_.resize(size_ * size_ * 6);
        int indiceOffset = 0;
        int halfSize = size_ / 2;

        // Top Left
        for(int z = 0; z < halfSize; z++)
        {
            for(int x = 0; x < halfSize; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        topLeftEndIndex_ = indiceOffset;

        // Top right
        for(int z = 0; z < halfSize; z++)
        {
            for(int x = halfSize; x < size_; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        topRightEndIndex_ = indiceOffset;

        // Bottom left
        for(int z = halfSize; z < size_; z++)
        {
            for(int x = 0; x < halfSize; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        bottomLeftEndIndex_ = indiceOffset;

        // Bottom right
        for(int z = halfSize; z < size_; z++)
        {
            for(int x = halfSize; x < size_; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        bottomRightEndIndex_ = indiceOffset;

        // Setup buffers (VAO, etc).
        setupBuffer();
    }

    void CDLODObjectChunk::drawChunk(int _indicesCount, int _indicesIndexLocation)
    {
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT,
            reinterpret_cast<void*>(_indicesIndexLocation));
    }
}
