#ifndef NAGE_ENGINE_GENERATORS_FLOWMAP_H_
#define NAGE_ENGINE_GENERATORS_FLOWMAP_H_

#include "itexturegenerator.h"

namespace mr::nage
{
    class FlowMap : public ITextureGenerator
    {
    public:
        FlowMap() {}

        void loadFromFile(const std::string& _path) override;
        void createTextureFromData(int _width, int _height, unsigned char* _data) override;
    };
}

#endif // NAGE_ENGINE_GENERATORS_FLOWMAP_H_
