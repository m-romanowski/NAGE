#ifndef NAGE_ENGINE_GENERATORS_NORMALMAP_H_
#define NAGE_ENGINE_GENERATORS_NORMALMAP_H_

#include "itexturegenerator.h"

namespace mr::nage
{
    class NormalMap : public ITextureGenerator
    {
    public:
        NormalMap();

        void loadFromFile(const std::string& _path) override;
        void createTextureFromData(int _width, int _height, unsigned char* _data) override;
    };
}

#endif // NAGE_ENGINE_GENERATORS_NORMALMAP_H_
