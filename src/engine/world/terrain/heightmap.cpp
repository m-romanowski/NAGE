#include "engine/components/image.h"
#include "heightmap.h"

#include <QDebug>

namespace NAGE
{
    HeightMap::HeightMap()
        : mHeightMapTexture(nullptr)
    {

    }

    HeightMap::~HeightMap()
    {
        delete mHeightMapTexture;
    }

    float HeightMap::heightAt(int _x, int _z) const
    {
        assert(_x >= 0 && _x < width() && _z >= 0 && _z < height());
        return (mData[_z * width() + _x] * 0.2);
    }

    float HeightMap::minValueFromArea(int _x, int _z, int _xOffset, int _zOffset) const
    {
        assert(_x >= 0 && _x < width() && _z >= 0 && _z < height());

        float minValue = 65535; // short (see: CDLOD documentation)
        for(int x = _x; x < _x + _xOffset; x++)
        {
            for(int z = _z; z < _z + _zOffset; z++)
            {
                minValue = std::min(minValue, heightAt(x, z));
            }
        }

        return minValue;
    }

    float HeightMap::maxValueFromArea(int _x, int _z, int _xOffset, int _zOffset) const
    {
        assert(_x >= 0 && _x < width() && _z >= 0 && _z < height());

        float maxValue = 0;
        for(int x = _x; x < _x + _xOffset; x++)
        {
            for(int z = _z; z < _z + _zOffset; z++)
            {
                maxValue = std::max(maxValue, heightAt(x, z));
            }
        }

        return maxValue;
    }

    int HeightMap::width() const
    {
        return mHeightMapTexture->width();
    }

    int HeightMap::height() const
    {
        return mHeightMapTexture->height();
    }

    Size<int> HeightMap::size() const
    {
        return Size<int>(mHeightMapTexture->width(), mHeightMapTexture->height());
    }

    GLuint HeightMap::textureId() const
    {
        return mHeightMapTexture->id();
    }

    void HeightMap::flat(int _width, int _height)
    {
        assert(_width > 0 && _height > 0);

        for(int z = 0; z < _height; z++)
        {
            for(int x = 0; x < _width; x++)
            {
                //setValue(x, z, 0.0f);
            }
        }
    }

    void HeightMap::flat(Size<int> _size)
    {
        flat(_size.width(), _size.height());
    }

    void HeightMap::perlinNoise(int _width, int _height, unsigned long _seed, FPerlinNoise::OctaveSettings _settings)
    {
        assert(_width > 0 && _height > 0);

        FPerlinNoise noise(_seed);
        if(noise.settings != _settings) noise.settings = _settings;

        for(int z = 0; z < _height; z++)
        {
            for(int x = 0; x < _width; x++)
            {
                //setValue(x, z, noise.FBM(x / mScale, z / mScale, 0) * mScale);
            }
        }
    }

    void HeightMap::perlinNoise(Size<int> _size, unsigned long _seed, FPerlinNoise::OctaveSettings _settings)
    {
        perlinNoise(_size.width(), _size.height(), _seed, _settings);
    }

    void HeightMap::diamondSquare(int _width, int _height)
    {
        assert(_width % 2 == 1 && _height % 2 == 1); // 2 ^ n + 1

        DiamondSquare noise(_width, _height);

        for(int z = 0; z < _height; z++)
        {
            for(int x = 0; x < _width; x++)
            {
                // setValue(x, z, noise.value(x / mScale, z / mScale) * mScale);
            }
        }
    }

    void HeightMap::diamondSquare(Size<int> _size)
    {
        diamondSquare(_size.width(), _size.height());
    }

    void HeightMap::loadFromFile(const std::string& _path)
    {
        mHeightMapTexture = new Texture(_path, TextureType::TEXTURE_2D);
        mData = mHeightMapTexture->redColorData();
    }
}
