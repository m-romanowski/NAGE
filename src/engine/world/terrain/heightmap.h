#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "engine/render/color.h"
#include "engine/world/primitives/plane.h"
#include "engine/world/procedural/perlinnoise.h"

namespace NAGE
{
    class HeightMap
    {
    public:
        // Available noise types
        enum NoiseType
        {
            Perlin,
            Simplex,
            Fractal
        };

        HeightMap();

        float** generateFromNoise(int _width, int _height, NoiseType _type);
        float** fromFile(const std::string& _path) const;
        void toFile(float** _heightMap, const std::string& _path);
    };
}

#endif // HEIGHTMAP_H
