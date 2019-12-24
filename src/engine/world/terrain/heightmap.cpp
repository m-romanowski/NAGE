#include "heightmap.h"

namespace NAGE
{
    HeightMap::HeightMap()
    {

    }

    float** HeightMap::generateFromNoise(int _width, int _height, NoiseType _type)
    {
        // Allocate memory
        float** heightMap = new float*[static_cast<unsigned long>(_width)];
        for(int i = 0; i < _width; i++)
            heightMap[i] = new float[static_cast<unsigned long>(_height)];

        FPerlinNoise noise(346346);
        noise.settings.frequency = 0.0009f;
        noise.settings.persistence = 0.3f;
        noise.settings.octaves = 10;
        noise.settings.amplitude = 15.0f;

        // Store noise heights.
        for(int x = 0; x < _width; x++)
        {
            for(int y = 0; y < _height; y++)
            {
                switch(_type)
                {
                    case NoiseType::Perlin:
                        heightMap[x][y] = noise.FBM(x, y, 0) * 300;
                        break;
                    case NoiseType::Fractal:
                        break;
                    case NoiseType::Simplex:
                        break;
                }
            }
        }

        return heightMap;
    }

    float** HeightMap::fromFile(const std::string& _path) const
    {
        // TODO
    }

    void HeightMap::toFile(float** _heightMap, const std::string& _path)
    {
        // TODO
    }
}
