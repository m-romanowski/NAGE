#ifndef QNAGE_INTERFACE_ISCENERESOURCE_H_
#define QNAGE_INTERFACE_ISCENERESOURCE_H_

#include <string>
#include <QImage>

namespace mr::qnage
{
    class ISceneResource
    {
    public:
        virtual void mapTexture(const std::string _materialName, QImage _image) = 0;
        virtual bool isNotEmpty() const = 0;
    };
}

#endif // QNAGE_INTERFACE_ISCENERESOURCE_H_
