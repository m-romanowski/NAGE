#include "engine/components/image.h"
#include "heightmap.h"

namespace mr::nage
{
    HeightMap::HeightMap()
    {

    }

    float HeightMap::heightAt(int _x, int _z) const
    {
        assert(_x >= 0 && _x < width() && _z >= 0 && _z < height());
        return (data_[_z * width() + _x] / std::numeric_limits<float>::max()) * HEIGHTMAP_MAX_HEIGHT;
    }

    void HeightMap::setValue(int _x, int _y, int _width, unsigned char* _data, Color _color)
    {
        _data[(_y * _width + _x) + 0] = std::floor(_color.red());
        _data[(_y * _width + _x) + 1] = std::floor(_color.green());
        _data[(_y * _width + _x) + 2] = std::floor(_color.blue());
    }

    void HeightMap::createTextureFromData(int _width, int _height, unsigned char* _data)
    {
        texture_ = std::make_unique<Texture>(TextureType::TEXTURE_2D);
        texture_->fromData(_width, _height, Texture::TextureFormat::RGB, _data);
        data_ = texture_->redColorData();
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


    Size<int> HeightMap::size() const
    {
        return Size<int>(texture_->width(), texture_->height());
    }

    void HeightMap::flat(int _width, int _height)
    {
        assert(_width > 0 && _height > 0);

        if(texture_)
            texture_ = std::make_unique<Texture>();

        unsigned char* data = new unsigned char[_width * _height * 3]; // RGB format
        for(int x = 0; x < _width; x++)
        {
            for(int y = 0; y < _height; y++)
                setValue(x, y, _width, data, Color(255, 255, 255));
        }

        createTextureFromData(_width, _height, data);
    }

    void HeightMap::flat(Size<int> _size)
    {
        flat(_size.width(), _size.height());
    }

    void HeightMap::perlinNoise(int _width, int _height, unsigned long _seed, FPerlinNoise::OctaveSettings _settings)
    {
        assert(_width > 0 && _height > 0);

        if(texture_)
            texture_ = std::make_unique<Texture>();

        FPerlinNoise noise(_seed);
        if(noise.settings != _settings) noise.settings = _settings;

        unsigned char* data = new unsigned char[_width * _height * 3]; // RGB format

        float fx = _width / noise.settings.frequency;
        float fy = _height / noise.settings.frequency;

        for(int x = 0; x < _width; x++)
        {
            for(int y = 0; y < _height; y++)
            {
                float noiseValue = noise.FBM(x / fx, y / fy, 0);
                setValue(x, y, _width, data, Color(noiseValue, noiseValue, noiseValue));
            }
        }

        createTextureFromData(_width, _height, data);
    }

    void HeightMap::perlinNoise(Size<int> _size, unsigned long _seed, FPerlinNoise::OctaveSettings _settings)
    {
        perlinNoise(_size.width(), _size.height(), _seed, _settings);
    }

    void HeightMap::diamondSquare(int _width, int _height)
    {
        assert(_width % 2 == 1 && _height % 2 == 1); // 2 ^ n + 1

        DiamondSquare noise(_width, _height);

        unsigned char* data = new unsigned char[_width * _height * 3]; // RGB format
        for(int x = 0; x < _width; x++)
        {
            for(int y = 0; y < _height; y++)
            {
                float noiseValue = noise.value(x, y);
                setValue(x, y, _width, data, Color(noiseValue, noiseValue, noiseValue));
            }
        }

        createTextureFromData(_width, _height, data);
    }

    void HeightMap::diamondSquare(Size<int> _size)
    {
        diamondSquare(_size.width(), _size.height());
    }

    void HeightMap::loadFromFile(const std::string& _path)
    {
        texture_ = std::make_unique<Texture>(_path, TextureType::TEXTURE_2D);
        data_ = texture_->redColorData();
    }
}
