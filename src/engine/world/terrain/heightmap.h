#ifndef NAGE_ENGINE_RENDER_TERRAIN_HEIGHTMAP_H_
#define NAGE_ENGINE_RENDER_TERRAIN_HEIGHTMAP_H_

#include "engine/util/size.h"
#include "engine/world/procedural/perlinnoise.h"
#include "engine/world/procedural/diamondsquare.h"

#include <cassert>

namespace NAGE
{
    class HeightMap
    {
    public:
        HeightMap();
        ~HeightMap();

        enum NoiseType
        {
            Perlin,
            Simplex,
            DSA // Diamond-square algorithm
        };

        // Getters
        float noise(int _x, int _z) const;
        float minValueFromArea(int _x, int _z, int _xOffset, int _zOffset);
        float maxValueFromArea(int _x, int _z, int _xOffset, int _zOffset);
        float scale() const;
        int width() const;
        int height() const;
        Size<int> size() const;

        // Setters
        void setScale(float _scale);

        void flat(int _width, int _height);
        void flat(Size<int> _size);
        void perlinNoise(Size<int> _size, unsigned long _seed = 0, FPerlinNoise::OctaveSettings _settings = FPerlinNoise::OctaveSettings());
        void perlinNoise(int _width, int _height, unsigned long _seed = 0, FPerlinNoise::OctaveSettings _settings = FPerlinNoise::OctaveSettings());
        void diamondSquare(Size<int> _size);
        void diamondSquare(int _width, int _height);

    private:
        void allocate();
        void deallocate();
        void setValue(int _x, int _z, float _value);

        float* mBuffer; // Buffer for the heightmap.
        float mScale; // Scale height (default height: <-1, 1>)
        int mWidth, mHeight; // Heightmap size.
    };
}

#endif // NAGE_ENGINE_RENDER_TERRAIN_HEIGHTMAP_H_
