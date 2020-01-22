#include "engine/render/vertexhelper.h"
#include "gridmesh.h"

namespace NAGE
{
    GridMesh::GridMesh(const Size<int> _size)
        : mWidth(_size.width()),
          mHeight(_size.height())
    {

    }

    GridMesh::GridMesh(int _width, int _height)
        : mWidth(_width),
          mHeight(_height)
    {

    }

    int GridMesh::width() const
    {
        return mWidth;
    }

    int GridMesh::height() const
    {
        return mHeight;
    }

    Size<int> GridMesh::size() const
    {
        return Size<int>(mWidth, mHeight);
    }

    void GridMesh::setWidth(int _width)
    {
        mWidth = _width;
        clearBuffers();
    }

    void GridMesh::setHeight(int _height)
    {
        mHeight = _height;
        clearBuffers();
    }

    void GridMesh::setSize(const Size<int> _size)
    {
        mWidth = _size.width();
        mHeight = _size.height();
        clearBuffers();
    }

    void GridMesh::setupMeshBuffers()
    {
        assert(mWidth > 0 && mHeight > 0);

        for(int z = 0; z <= mHeight; z++)
        {
            for(int x = 0; x <= mWidth; x++)
            {
                mVertices.push_back(
                    Vertex(Vector3f(x / mWidth, 0.0f, z / mHeight))
                );
            }
        }

        for(int z = 0; z < mHeight; z++)
        {
            for(int x = 0; x < mWidth; x++)
            {
                mIndices.push_back(x + (mWidth + 1) * z);
                mIndices.push_back((x + 1) + (mWidth + 1) * z);
                mIndices.push_back((x + 1) + (mWidth + 1) * (z + 1));
                mIndices.push_back((x + 1) + (mWidth + 1) * (z + 1));
                mIndices.push_back(x + (mWidth + 1) * (z + 1));
                mIndices.push_back(x + (mWidth + 1) * z);
            }
        }

        VertexHelper::calculateNormals(mVertices, mIndices);
        setupBuffer();
    }
}
