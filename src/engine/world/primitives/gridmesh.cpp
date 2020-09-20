#include "engine/render/vertexhelper.h"
#include "gridmesh.h"

namespace NAGE
{
    GridMesh::GridMesh(const Size<int> _size)
        : width_(_size.width()),
          height_(_size.height())
    {

    }

    GridMesh::GridMesh(int _width, int _height)
        : width_(_width),
          height_(_height)
    {

    }

    int GridMesh::width() const
    {
        return width_;
    }

    int GridMesh::height() const
    {
        return height_;
    }

    Size<int> GridMesh::size() const
    {
        return Size<int>(width_, height_);
    }

    void GridMesh::setWidth(int _width)
    {
        width_ = _width;
        clearBuffers();
    }

    void GridMesh::setHeight(int _height)
    {
        height_ = _height;
        clearBuffers();
    }

    void GridMesh::setSize(const Size<int> _size)
    {
        width_ = _size.width();
        height_ = _size.height();
        clearBuffers();
    }

    void GridMesh::setupMeshBuffers()
    {
        assert(width_ > 0 && height_ > 0);

        for(int z = 0; z <= height_; z++)
        {
            for(int x = 0; x <= width_; x++)
            {
                vertices_.push_back(
                    Vertex(Vector3f(x / width_, 0.0f, z / height_))
                );
            }
        }

        for(int z = 0; z < height_; z++)
        {
            for(int x = 0; x < width_; x++)
            {
                indices_.push_back(x + (width_ + 1) * z);
                indices_.push_back((x + 1) + (width_ + 1) * z);
                indices_.push_back((x + 1) + (width_ + 1) * (z + 1));
                indices_.push_back((x + 1) + (width_ + 1) * (z + 1));
                indices_.push_back(x + (width_ + 1) * (z + 1));
                indices_.push_back(x + (width_ + 1) * z);
            }
        }

        VertexHelper::calculateNormals(vertices_, indices_);
        setupBuffer();
    }
}
