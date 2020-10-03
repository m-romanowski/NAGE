#ifndef NAGE_ENGINE_COMPONENTS_IMAGE_H_
#define NAGE_ENGINE_COMPONENTS_IMAGE_H_

#include "STB/stb_image.h"
#include <string>

namespace mr::nage
{
    class Image
    {
    public:
        Image(const std::string& _path);
        ~Image();

        // Getters
        unsigned char* data();
        int width() const;
        int height() const;
        int format() const;

        void free();
        static void colorAt(unsigned char* _data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y,
            unsigned char* _red, unsigned char* _green, unsigned char* _blue, unsigned char* _alpha);
        static unsigned char red(unsigned char* _data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y);
        static unsigned char green(unsigned char* _data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y);
        static unsigned char blue(unsigned char* _data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y);
        static unsigned char alpha(unsigned char* _data, int _format, unsigned long _imageWidth, unsigned long _x, unsigned long _y);

    private:
        // Image properties
        int width_, height_, format_;
        unsigned char* data_;
    };
}

#endif // NAGE_ENGINE_COMPONENTS_IMAGE_H_
