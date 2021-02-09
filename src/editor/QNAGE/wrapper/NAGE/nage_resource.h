#ifndef QNAGE_WRAPPER_NAGE_RESOURCE_H_
#define QNAGE_WRAPPER_NAGE_RESOURCE_H_

#include "engine/render/resource.h"
#include "editor/QNAGE/interface/isceneresource.h"

#include <QByteArray>
#include <QBuffer>

namespace mr::qnage
{
    class NAGEResource
        : public ISceneResource
    {
    public:
        void mapTexture(const std::string _materialName, QImage _image) override
        {
            // int width = _image.width();
            // int height = _image.height();

            // QByteArray imageBytes;
            // QBuffer buffer(&imageBytes);
            // buffer.open(QIODevice::WriteOnly);
            // _image.save(&buffer, "PNG");

            // stbi_uc* data = reinterpret_cast<stbi_uc*>(imageBytes.data());
            // const int dataSize = imageBytes.size();

            // int imageWidth, imageHeight, imageChannels;
            // stbi_uc* imageData = stbi_load_from_memory(data, dataSize, &imageWidth, &imageHeight, &imageChannels, 4);
            
            // nage::Texture* texture = new nage::Texture(imageWidth, imageHeight, imageData, nage::TextureType::TEXTURE_2D);
            // this->resource_->mapTexture(_materialName, texture);
        }

        bool isNotEmpty() const override
        {
            return resource_ != nullptr;
        }

        static ISceneResource* from(nage::Resource* _resource)
        {
            return new NAGEResource(_resource);
        }

    private:
        NAGEResource(nage::Resource* _resource) : resource_(_resource) {}

        nage::Resource* resource_;
    };
}

#endif // QNAGE_WRAPPER_NAGE_RESOURCE_H_
