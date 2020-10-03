#include "geometryclipmap.h"

namespace mr::nage
{
    GeometryClipmap::GeometryClipmap()
    {

    }

    void GeometryClipmap::setupBuffers(int _size)
    {
        setupBlock(_size); // n x n block
        setupRingFixup(_size, 3); // n x 3 ring fix-up
        setupInteriorTrim(_size); // (2 x n - 1) x 2 interior trim
    }

    void GeometryClipmap::setupBlock(unsigned int _n)
    {
        // Vertices
        for(unsigned int z = 0; z < _n; z++)
        {
            for(unsigned int x = 0; x < _n; x++)
                block_.vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        // Indices
        unsigned int index = 0;
        block_.indices_.resize(_n * _n * 6);

        for (unsigned int z = 0; z < _n - 1; z++)
        {
            for (unsigned int x = 0; x < _n - 1; x++)
            {
                unsigned int offset = z * _n + x;

                block_.indices_[index] = offset;
                block_.indices_[index + 1] = offset + 1;
                block_.indices_[index + 2] = offset + _n;
                block_.indices_[index + 3] = offset + 1;
                block_.indices_[index + 4] = offset + _n + 1;
                block_.indices_[index + 5] = offset + _n;

                index += 6;
            }
        }
    }

    void GeometryClipmap::setupRingFixup(unsigned int _m, unsigned int _n)
    {
        // Vertices
        // Vertical
        for(unsigned int z = 0; z < _m; z++)
        {
            for(unsigned int x = 0; x < _n; x++)
                ringFixup_.vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        // Horizontal
        for(unsigned int z = 0; z < _n; z++)
        {
            for(unsigned int x = 0; x < _m; x++)
                ringFixup_.vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        // Indices
    }

    void GeometryClipmap::setupInteriorTrim(unsigned int _size)
    {
        // Interior trim - L-letter - (for each side: top, bottom, left, right).
        // size = (2 x m + 1) x 2
        // Top
        for(unsigned int z = 0; z < 2; z++)
        {
            for(unsigned int x = 0; x < 2 * _size + 1; x++)
                ringFixup_.vertices_.push_back(Vertex(Vector3f(x, 0.0f, z)));
        }

        // Bottom
        for(unsigned int z = 1; z >= 0 ; z--)
        {
            for(unsigned int x = 0; x < 2 * _size + 1; x++)
                ringFixup_.vertices_.push_back(Vertex(Vector3f(2 * _size - x, 0.0f, (2 * _size - 1) + z)));
        }

        // Left
        for(unsigned int x = 0; x < 2; x++)
        {
            for(unsigned int z = 0; z < 2 * _size + 1; z++)
                ringFixup_.vertices_.push_back(Vertex(Vector3f(x, 0.0f, 2 * _size - z)));
        }

        // Right
        for(unsigned int x = 1; x >= 0 ; x--)
        {
            for(unsigned int z = 0; z < 2 * _size + 1 ; z++)
                ringFixup_.vertices_.push_back(Vertex(Vector3f((2 * _size - 1) + x, 0.0f, z)));
        }
    }

    void GeometryClipmap::setupDegenerate(unsigned int _size)
    {

    }
}
