#ifndef QNAGE_WRAPPER_NAGE_SCENENODE_H_
#define QNAGE_WRAPPER_NAGE_SCENENODE_H_

#include "engine/core/scene/scenenode.h"
#include "interface/iscenenode.h"
#include "nage_sceneobject.h"
#include "nage_camera.h"

namespace mr::qnage
{
    class NAGESceneNode
        : public ISceneNode
    {
    public:
        std::string name() const override
        {
            return node_->name(); 
        }

        ICamera* camera() override
        {
            return camera_;
        }

        void removeFromScene(const std::string objectId) override
        {
            node_->removeFromScene(objectId);
        }

        std::vector<ISceneObject*> objects() const override
        {
            return NAGESceneObject::map(node_->renderableObjects());
        }

        static NAGESceneNode* from(nage::SceneNode* _node)
        {
            if(!_node)
                throw new std::invalid_argument("Cannot create item for not defined scene");

            return new NAGESceneNode(_node);
        }

        static std::vector<ISceneNode*> map(std::unordered_map<std::string, nage::SceneNode*> _nodes)
        {
            std::vector<ISceneNode*> result;
            for(auto node : _nodes)
                result.push_back(NAGESceneNode::from(node.second));

            return result;
        }

    private:
        NAGESceneNode(nage::SceneNode* _node) : node_(_node), camera_(NAGECamera::from(_node->camera())) {}

        nage::SceneNode* node_;
        ICamera* camera_;
    };
}

#endif // QNAGE_WRAPPER_NAGE_SCENENODE_H_
