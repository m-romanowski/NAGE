#include "scenetree.h"

namespace mr::qnage
{
    SceneTree::SceneTree(QWidget* _parent)
        : QTreeWidget(_parent)
    {
        this->setObjectName("scene-tree");
        this->setContentsMargins(5, 20, 5, 20);
        this->setHeaderLabel("Scene manager");

        connect(this, &QTreeWidget::itemClicked, this, &SceneTree::onClicked);
    }

    void SceneTree::setSceneHandler(ISceneManager* _sceneManager)
    {
        sceneManager_ = _sceneManager;
        for(auto sceneNode : sceneManager_->scenes())
        {
            auto sceneTreeNode = addToTree(sceneNode);

            // Add camera.
            sceneTreeNode->addCamera(sceneNode->camera());
            if(auto child = sceneTreeNode->activeChild(); child.has_value())
                onClicked(child.value(), 0);

            // Add renderable objects.
            for(auto object : sceneNode->objects())
                sceneTreeNode->addItem(object);
        }
    }

    void SceneTree::addScene(const QString _sceneName)
    {
        if(_sceneName.isEmpty())
            throw std::runtime_error("Cannot add scene with empty name");

        if(!isChildNodeExist(_sceneName))
        {
            auto sceneNode = sceneManager_->addChild(_sceneName.toStdString());
            addToTree(sceneNode);
        }
    }

    void SceneTree::removeScene()
    {
        if(auto childNodeOpt = activeChildNode(); childNodeOpt.has_value())
        {
            auto childNode = childNodeOpt.value();
            sceneManager_->removeChild(childNode->name().toStdString());

            delete childNode;
        }
    }

    SceneTreeNode* SceneTree::addToTree(ISceneNode* _sceneNode)
    {
        auto sceneTreeNode = new SceneTreeNode(_sceneNode);
        addTopLevelItem(sceneTreeNode);

        if(topLevelItemCount() < 2)
            sceneTreeNode->setExpanded(true);

        return sceneTreeNode;
    }

    std::optional<SceneTreeNode*> SceneTree::activeChildNode()
    {
        if(auto item = currentItem(); item)
            return std::optional<SceneTreeNode*>{ static_cast<SceneTreeNode*>(item) };

        return std::nullopt;
    }

    bool SceneTree::isChildNodeExist(const QString _sceneName)
    {
        for(int i = 0; i < topLevelItemCount(); i++)
        {
            if(auto item = topLevelItem(i); item)
            {
                if(item->text(0) == _sceneName)
                    return true;
            }
        }

        return false;
    }

    void SceneTree::onClicked(QTreeWidgetItem* _item, int _column)
    {
        if(ISceneTreeNodeItem* castedItem = dynamic_cast<ISceneTreeNodeItem*>(_item))
            emit transformationsForNode(castedItem->transformations());
    }
}
