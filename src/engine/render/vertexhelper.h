#ifndef NAGE_ENGINE_RENDER_VERTEXHELPER_H_
#define NAGE_ENGINE_RENDER_VERTEXHELPER_H_

#include "vertex.h"
#include "glad/glad.h"

#include <vector>

namespace NAGE
{
    class VertexHelper
    {
    public:
        static void calculateNormals(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices)
        {
            for(unsigned int i = 0; i < _indices.size(); i += 3)
            {
                unsigned int i0 = _indices[i];
                unsigned int i1 = _indices[i + 1];
                unsigned int i2 = _indices[i + 2];

                Vector3f v1 = _vertices[i1].position_ - _vertices[i0].position_;
                Vector3f v2 = _vertices[i2].position_ - _vertices[i0].position_;

                Vector3f normal = Vector3f::normalize(Vector3f::cross(v1, v2));

                _vertices[i0].normal_ += normal;
                _vertices[i1].normal_ += normal;
                _vertices[i2].normal_ += normal;
            }

            for(unsigned int i = 0; i < _vertices.size(); i++)
                _vertices[i].normal_ = Vector3f::normalize(_vertices[i].normal_);
        }
    };
}

#endif // NAGE_ENGINE_RENDER_VERTEXHELPER_H_
