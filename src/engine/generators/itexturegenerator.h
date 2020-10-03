#ifndef NAGE_ENGINE_GENERATORS_ITEXTUREGENERATOR_H_
#define NAGE_ENGINE_GENERATORS_ITEXTUREGENERATOR_H_

#include "engine/render/texture.h"

#include <string>
#include <memory>

namespace mr::nage
{
    class ITextureGenerator
    {
    public:
        ITextureGenerator() {}

        inline int width() const
        {
            if(texture_)
                return texture_->width();

            return -1;
        }

        inline int height() const
        {
            if(texture_)
                return texture_->height();

            return -1;
        }

        inline GLuint textureId() const
        {
            if(texture_)
                return texture_->id();

            return 0;
        }

    protected:
        virtual void loadFromFile(const std::string& _path) = 0;
        virtual void createTextureFromData(int _width, int _height, unsigned char* _data) = 0;

        std::unique_ptr<Texture> texture_;
    };
}

#endif // NAGE_ENGINE_GENERATORS_ITEXTUREGENERATOR_H_
