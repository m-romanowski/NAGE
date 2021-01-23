#ifndef QNAGE_WRAPPER_NAGE_SCENEMANAGER_H_
#define QNAGE_WRAPPER_NAGE_SCENEMANAGER_H_

#include "engine/core/scene/scenemanager.h"
#include "interface/iscenemanager.h"
#include "nage_scenenode.h"

namespace mr::qnage
{
    class NAGESceneManager
        : public ISceneManager
    {
    public:
        std::vector<ISceneNode*> scenes() const override
        {
            return NAGESceneNode::map(manager_->scenes());
        }

        ISceneNode* addChild(const std::string& _key) override
        {
            return NAGESceneNode::from(manager_->addChild(_key));
        }

        void removeChild(const std::string& _key) override
        {
            manager_->removeChild(_key);
        }

        static NAGESceneManager* from(nage::SceneManager* _manager)
        {
            if(!_manager)
                throw new std::invalid_argument("Cannot create item for not defined scene manager");

            return new NAGESceneManager(_manager);
        }

    private:
        NAGESceneManager(nage::SceneManager* _manager) : manager_(_manager) {}

        nage::SceneManager* manager_;
    };
}

#endif // QNAGE_WRAPPER_NAGE_SCENEMANAGER_H_
