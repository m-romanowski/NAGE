#include "heightmap.h"

namespace NAGE
{
    HeightMap::HeightMap()
        : mBuffer(nullptr),
          mScale(1.0f),
          mWidth(0),
          mHeight(0)
    {

    }

    HeightMap::~HeightMap()
    {
        if(mBuffer)
            delete[] mBuffer;
    }

    float HeightMap::noise(int _x, int _z) const
    {
        return mBuffer[_x * mHeight + _z];
    }

    float HeightMap::minValueFromArea(int _x, int _z, int _xOffset, int _zOffset)
    {
        assert(_x >= 0 && _x < mWidth && _z >=0 && _z < mHeight);

        float minValue = mBuffer[_x * mHeight + _z];
        for(int z = _z + 1; z < _z + _zOffset; z++)
        {
            for(int x = _x + 1; x < _x + _xOffset; x++)
            {
                if(minValue < mBuffer[_x * mHeight + _z])
                    minValue = mBuffer[_x + mHeight + _z];
            }
        }

        return minValue;
    }

    float HeightMap::maxValueFromArea(int _x, int _z, int _xOffset, int _zOffset)
    {
        assert(_x >= 0 && _x < mWidth && _z >=0 && _z < mHeight);

        float maxValue = mBuffer[_x * mHeight + _z];
        for(int z = _z + 1; z < _z + _zOffset; z++)
        {
            for(int x = _x + 1; x < _x + _xOffset; x++)
            {
                if(maxValue > mBuffer[_x * mHeight + _z])
                    maxValue = mBuffer[_x + mHeight + _z];
            }
        }

        return maxValue;
    }

    float HeightMap::scale() const
    {
        return mScale;
    }

    int HeightMap::width() const
    {
        return mWidth;
    }

    int HeightMap::height() const
    {
        return mHeight;
    }

    Size<int> HeightMap::size() const
    {
        return Size<int>(mWidth, mHeight);
    }

    void HeightMap::setScale(float _scale)
    {
        mScale = _scale;
    }

    void HeightMap::setValue(int _x, int _z, float _value)
    {
        mBuffer[_x * mHeight + _z] = _value;
    }

    void HeightMap::allocate()
    {
        assert(mWidth > 0 && mHeight > 0);
        mBuffer = new float[mWidth * mHeight];

        for(int z = 0; z < mHeight; z++)
        {
            for(int x = 0; x < mWidth; x++)
            {
                setValue(x, z, 0);
            }
        }
    }

    void HeightMap::flat(int _width, int _height)
    {
        assert(_width > 0 && _height > 0);

        // Allocate memory.
        mWidth = _width;
        mHeight = _height;
        allocate();

        for(int z = 0; z < mHeight; z++)
        {
            for(int x = 0; x < mWidth; x++)
            {
                setValue(x, z, 0.0f);
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

        // Allocate memory.
        mWidth = _width;
        mHeight = _height;
        allocate();

        FPerlinNoise noise(_seed);
        if(noise.settings != _settings) noise.settings = _settings;

        for(int z = 0; z < mHeight; z++)
        {
            for(int x = 0; x < mWidth; x++)
            {
                setValue(x, z, noise.FBM(x, z, 0) * mScale);
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

        mWidth = _width;
        mHeight = _height;
        allocate();

        DiamondSquare noise(_width, _height);

        for(int z = 0; z < mHeight; z++)
        {
            for(int x = 0; x < mWidth; x++)
            {
                setValue(x, z, noise.value(x, z) * mScale);
            }
        }
    }

    void HeightMap::diamondSquare(Size<int> _size)
    {
        diamondSquare(_size.width(), _size.height());
    }
}
