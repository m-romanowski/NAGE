#ifndef QNAGE_INTERFACE_ISCENEOBJECT_H_
#define QNAGE_INTERFACE_ISCENEOBJECT_H_

#include <string>
#include "isceneobjecttransformation.h"
#include "isceneresource.h"

namespace mr::qnage
{
    class ISceneObject
    {
    public:
        virtual std::string id() const = 0;
        virtual ISceneObjectTransformation* transformation() = 0;
        virtual ISceneResource* resource() = 0;

        bool isTransformable()
        {
            return transformation()->isAvailable();
        }

        bool hasResource()
        {
            return resource()->isNotEmpty();
        }
    };
}

#endif // QNAGE_INTERFACE_ISCENEOBJECT_H_
