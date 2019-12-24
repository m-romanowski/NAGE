#ifndef NAGE_COMPONENTS_IMAGE_H_
#define NAGE_COMPONENTS_IMAGE_H_

#include "STB/stb_image.h"
#include <string>

namespace NAGE
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
        static void getPixel(unsigned char* _data, unsigned long _imageWidth, unsigned long _x, unsigned long _y,
            unsigned char* _red, unsigned char* _green, unsigned char* _blue, unsigned char* _alpha);

    private:
        // Image properties
        int mWidth, mHeight, mFormat;
        unsigned char* mData;
    };
}

#endif // NAGE_COMPONENTS_IMAGE_H_
