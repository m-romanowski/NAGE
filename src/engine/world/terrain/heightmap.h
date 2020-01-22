#ifndef NAGE_ENGINE_WORLD_TERRAIN_HEIGHTMAP_H_
#define NAGE_ENGINE_WORLD_TERRAIN_HEIGHTMAP_H_

#include "glad/glad.h"
#include "engine/util/size.h"
#include "engine/render/model/texture.h"
#include "engine/world/procedural/perlinnoise.h"
#include "engine/world/procedural/diamondsquare.h"

#include <cassert>
#include <climits>

#define HEIGHTMAP_MAX_HEIGHT 255

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
        float heightAt(int _x, int _z) const;
        float minValueFromArea(int _x, int _z, int _xOffset, int _zOffset) const;
        float maxValueFromArea(int _x, int _z, int _xOffset, int _zOffset) const;
        int width() const;
        int height() const;
        Size<int> size() const;
        GLuint textureId() const;

        void flat(int _width, int _height);
        void flat(Size<int> _size);
        void perlinNoise(Size<int> _size, unsigned long _seed = 0,
            FPerlinNoise::OctaveSettings _settings = FPerlinNoise::OctaveSettings());
        void perlinNoise(int _width, int _height, unsigned long _seed = 0,
            FPerlinNoise::OctaveSettings _settings = FPerlinNoise::OctaveSettings());
        void diamondSquare(Size<int> _size);
        void diamondSquare(int _width, int _height);
        void loadFromFile(const std::string& _path);

    private:
        std::vector<unsigned char> mData; // Height map data (based on red color).
        Texture* mHeightMapTexture;
    };
}

#endif // NAGE_ENGINE_WORLD_TERRAIN_HEIGHTMAP_H_
