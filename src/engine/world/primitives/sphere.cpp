#include "engine/render/vertexhelper.h"
#include "sphere.h"

namespace mr::nage
{
    Sphere::Sphere(const std::string& _id, unsigned int _sectorCount, unsigned int _stackCount, float _radius)
        : Primitive(_id),
          sectorCount_(_sectorCount),
          stackCount_(_stackCount),
          radius_(_radius)
    {
        generateSphere(vertices_, indices_, _sectorCount, _stackCount, _radius);
    }

    unsigned int Sphere::stackCount() const
    {
        return stackCount_;
    }

    unsigned int Sphere::sectorCount() const
    {
        return sectorCount_;
    }

    float Sphere::radius() const
    {
        return radius_;
    }

    void Sphere::setSectorCount(unsigned int _count)
    {
        sectorCount_ = _count;
    }

    void Sphere::setStackCount(unsigned int _count)
    {
        stackCount_ = _count;
    }

    void Sphere::setRadius(float _radius)
    {
        radius_ = _radius;
    }

    void Sphere::setupPrimitive()
    {
        setupBuffer();
    }

    /* Generate the sphere.
     *
     * Sector:
     * x = (r * cos(φ)) * cos(θ)
     * y = (r * cos(φ)) * sin(θ)
     * z = r * sin(φ)
     *
     * θ = 2π * sectorStep / sectorCOunt
     * φ = 0.5π - π * (stackStep / stackCount)
     */
    void Sphere::generateSphere(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices,
        unsigned int _sectorCount, unsigned int _stackCount, float _radius)
    {
        // Vertices
        float sectorStep = 2.0f * M_PI / _sectorCount;
        float stackStep = M_PI / _stackCount;

        for(unsigned int i = 0; i <= _stackCount; i++)
        {
            float stackAngle = 0.5f * M_PI - i * stackStep;
            float xy = _radius * std::cos(stackAngle);
            float z = _radius * std::sin(stackAngle);

            for(unsigned int j = 0; j <= _sectorCount; j++)
            {
                float sectorAngle = j * sectorStep;

                float x = xy * std::cos(sectorAngle);
                float y = xy * std::sin(sectorAngle);
                float tx = static_cast<float>(j) / _sectorCount;
                float ty = static_cast<float>(i) / _stackCount;

                // Calculate normals later (after append indices).
                _vertices.push_back(Vertex(Vector3f(x, y, z), Vector2f(tx, ty)));
            }
        }

        // Indices
        for(unsigned int i = 0; i < _stackCount; i++)
        {
            unsigned int indice1 = i * (_sectorCount + 1);
            unsigned int indice2 = indice1 + _sectorCount + 1;

            for(unsigned int j = 0; j < _sectorCount; j++)
            {
                // Two trangles per sector.
                if(i != 0)
                {
                    _indices.push_back(indice1);
                    _indices.push_back(indice2);
                    _indices.push_back(indice1 + 1);
                }

                if(i != (_stackCount - 1))
                {
                    _indices.push_back(indice1 + 1);
                    _indices.push_back(indice2);
                    _indices.push_back(indice2 + 1);
                }

                indice1++;
                indice2++;
            }
        }

        // Normals
        VertexHelper::calculateNormals(_vertices, _indices);
    }
}
