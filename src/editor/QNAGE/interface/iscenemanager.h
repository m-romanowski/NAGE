#ifndef QNAGE_INTERFACE_ISCENEMANAGER_H_
#define QNAGE_INTERFACE_ISCENEMANAGER_H_

#include <vector>
#include "iscenenode.h"

namespace mr::qnage
{
    class ISceneManager
    {
    public:
        virtual std::vector<ISceneNode*> scenes() const = 0;
        virtual ISceneNode* addChild(const std::string& _key) = 0;
        virtual void removeChild(const std::string& _key) = 0;
    };
}

#endif // QNAGE_INTERFACE_ISCENEMANAGER_H_
