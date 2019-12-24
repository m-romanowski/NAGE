#include "image.h"

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #include "STB/stb_image.h"
#endif

namespace NAGE
{
    Image::Image(const std::string& _path)
    {
        mData = stbi_load(_path.c_str(), &mWidth, &mHeight, &mFormat, 0);
    }

    Image::~Image()
    {

    }

    unsigned char* Image::data()
    {
        return mData;
    }

    int Image::width() const
    {
        return mWidth;
    }

    int Image::height() const
    {
        return mHeight;
    }

    int Image::format() const
    {
        return mFormat;
    }

    void Image::free()
    {
        if(mData)
            stbi_image_free(mData);
    }

    void Image::getPixel(unsigned char* _data, unsigned long _imageWidth, unsigned long _x, unsigned long _y,
        unsigned char* _red, unsigned char* _green, unsigned char* _blue, unsigned char* _alpha)
    {
        *_red = _data[4 * (_y * _imageWidth + _x) + 0];
        *_green = _data[4 * (_y * _imageWidth + _x) + 1];
        *_blue = _data[4 * (_y * _imageWidth + _x) + 2];
        *_alpha = _data[4 * (_y * _imageWidth + _x) + 3];
    }
}
