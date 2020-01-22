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

    void Image::colorAt(unsigned char* _data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y,
        unsigned char* _red, unsigned char* _green, unsigned char* _blue, unsigned char* _alpha)
    {
        *_red = red(_data, _format, _imageWidth, _x, _y);
        *_green = green(_data, _format, _imageWidth, _x, _y);
        *_blue = blue(_data, _format, _imageWidth, _x, _y);
        *_alpha = alpha(_data, _format, _imageWidth, _x, _y);
    }

    unsigned char Image::red(unsigned char *_data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y)
    {
        return _data[_format * (_y * _imageWidth + _x) + 0];
    }

    unsigned char Image::green(unsigned char *_data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y)
    {
        return _data[_format * (_y * _imageWidth + _x) + 1];
    }

    unsigned char Image::blue(unsigned char *_data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y)
    {
        return _data[_format * (_y * _imageWidth + _x) + 2];
    }

    unsigned char Image::alpha(unsigned char *_data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y)
    {
        return _format >= 4 ? _data[_format * (_y * _imageWidth + _x) + 3] : 0xff;
    }
}
