#ifndef NAGE_ENGINE_GENERATORS_HEIGHTMAP_H_
#define NAGE_ENGINE_GENERATORS_HEIGHTMAP_H_

#include "glad/glad.h"
#include "engine/util/size.h"
#include "engine/render/color.h"
#include "engine/world/procedural/perlinnoise.h"
#include "engine/world/procedural/diamondsquare.h"
#include "itexturegenerator.h"

#include <cassert>
#include <climits>

#define HEIGHTMAP_MAX_HEIGHT 255

namespace NAGE
{
    class HeightMap : public ITextureGenerator
    {
    public:
        HeightMap();

        enum NoiseType
        {
            Perlin,
            Simplex,
            DSA // Diamond-square algorithm
        };

        // Getters
        float heightAt(int _x, int _z) const;
        float minValueFromArea(int _x, int _z, int _xOffset, int _zOffset) const;
        float maxValueFromArea(int _x, int _z, int _xOffset, int _zOffset) const;
        Size<int> size() const;

        void flat(int _width, int _height);
        void flat(Size<int> _size);
        void perlinNoise(Size<int> _size, unsigned long _seed = 0,
            FPerlinNoise::OctaveSettings _settings = FPerlinNoise::OctaveSettings());
        void perlinNoise(int _width, int _height, unsigned long _seed = 0,
            FPerlinNoise::OctaveSettings _settings = FPerlinNoise::OctaveSettings());
        void diamondSquare(Size<int> _size);
        void diamondSquare(int _width, int _height);

        // Abstract implementations.
        void loadFromFile(const std::string& _path) override;
        void createTextureFromData(int _width, int _height, unsigned char* _data) override;

    private:
        void setValue(int _x, int _y, int _width, unsigned char* _data, Color _color);

        std::vector<unsigned char> data_; // Height map data (based on red color).
    };
}

#endif // NAGE_ENGINE_GENERATORS_HEIGHTMAP_H_
