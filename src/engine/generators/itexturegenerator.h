#ifndef NAGE_ENGINE_GENERATORS_ITEXTUREGENERATOR_H_
#define NAGE_ENGINE_GENERATORS_ITEXTUREGENERATOR_H_

#include "engine/render/texture.h"

#include <string>
#include <memory>

namespace NAGE
{
    class ITextureGenerator
    {
    public:
        ITextureGenerator() {}

        inline int width() const
        {
            if(mTexture)
                return mTexture->width();

            return -1;
        }

        inline int height() const
        {
            if(mTexture)
                return mTexture->height();

            return -1;
        }

        inline GLuint textureId() const
        {
            if(mTexture)
                return mTexture->id();

            return 0;
        }

    protected:
        virtual void loadFromFile(const std::string& _path) = 0;
        virtual void createTextureFromData(int _width, int _height, unsigned char* _data) = 0;

        std::unique_ptr<Texture> mTexture;
    };
}

#endif // NAGE_ENGINE_GENERATORS_ITEXTUREGENERATOR_H_
