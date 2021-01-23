#ifndef QNAGE_INTERFACE_ICAMERA_H_
#define QNAGE_INTERFACE_ICAMERA_H_

#include <functional>
#include "isceneobject.h"

namespace mr::qnage
{
    class ICamera
        : public ISceneObject
    {
    public:
        virtual void onTranslation(std::function<void(ISceneObjectTransformation::Vec3)> _callback) = 0;
        virtual void onRotation(std::function<void(ISceneObjectTransformation::Vec3)> _callback) = 0;
    };
}

#endif // QNAGE_INTERFACE_ICAMERA_H_
