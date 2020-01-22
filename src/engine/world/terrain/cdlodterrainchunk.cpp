#include "cdlodterrainchunk.h"

namespace NAGE
{
    CDLODTerrainChunk::CDLODTerrainChunk(int _size)
        : mSize(_size)
    {
        setupMeshBuffers();
    }

    int CDLODTerrainChunk::topLeftEndIndex() const
    {
        return mTopLeftEndIndex;
    }

    int CDLODTerrainChunk::topRightEndIndex() const
    {
        return mTopRightEndIndex;
    }

    int CDLODTerrainChunk::bottomLeftEndIndex() const
    {
        return mBottomLeftEndIndex;
    }

    int CDLODTerrainChunk::bottomRightEndIndex() const
    {
        return mBottomRightEndIndex;
    }

    int CDLODTerrainChunk::size() const
    {
        return mSize;
    }

    void CDLODTerrainChunk::appendIndices(int _x, int _z, int _size, int& _currentOffset)
    {
        mIndices[_currentOffset++] = (_x + _size * _z);
        mIndices[_currentOffset++] = ((_x + 1) + _size * _z);
        mIndices[_currentOffset++] = ((_x + 1) + _size * (_z + 1));
        mIndices[_currentOffset++] = ((_x + 1) + _size * (_z + 1));
        mIndices[_currentOffset++] = (_x + _size * (_z + 1));
        mIndices[_currentOffset++] = (_x + _size * _z);
    }

    void CDLODTerrainChunk::setupMeshBuffers()
    {
        assert(mSize > 0);

        const int dim = mSize + 1;

        // Vertices
        for(int x = 0; x < dim; x++)
        {
            for(int z = 0; z < dim; z++)
            {
                float xx = (x - mSize / 2);
                float zz = (z - mSize / 2);
                xx = x;
                zz = z;

                mVertices.push_back(
                    Vertex(Vector3f(xx / mSize, 0.0f, zz / mSize))
                );
            }
        }

        // Indices
        mIndices.resize(mSize * mSize * 6);
        int indiceOffset = 0;
        int halfSize = mSize / 2;

        // Top Left
        for(int z = 0; z < halfSize; z++)
        {
            for(int x = 0; x < halfSize; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        mTopLeftEndIndex = indiceOffset;

        // Top right
        for(int z = 0; z < halfSize; z++)
        {
            for(int x = halfSize; x < mSize; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        mTopRightEndIndex = indiceOffset;

        // Bottom left
        for(int z = halfSize; z < mSize; z++)
        {
            for(int x = 0; x < halfSize; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        mBottomLeftEndIndex = indiceOffset;

        // Bottom right
        for(int z = halfSize; z < mSize; z++)
        {
            for(int x = halfSize; x < mSize; x++)
            {
                appendIndices(x, z, dim, indiceOffset);
            }
        }

        mBottomRightEndIndex = indiceOffset;

        // Setup buffers (VAO, etc).
        setupBuffer();
    }

    void CDLODTerrainChunk::drawChunk(int _indicesCount, int _indicesIndexLocation)
    {
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT,
            reinterpret_cast<void*>(_indicesIndexLocation));
    }
}
