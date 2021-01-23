#ifndef QNAGE_INTERFACE_ISCENENODE_H_
#define QNAGE_INTERFACE_ISCENENODE_H_

#include "icamera.h"

namespace mr::qnage
{
    class ISceneNode
    {
    public:
        virtual std::string name() const = 0;
        virtual ICamera* camera() = 0;
        virtual void removeFromScene(const std::string objectId) = 0;
        virtual std::vector<ISceneObject*> objects() const = 0;
    };
}

#endif // QNAGE_INTERFACE_ISCENENODE_H_
