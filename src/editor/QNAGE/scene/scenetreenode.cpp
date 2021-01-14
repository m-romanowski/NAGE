#include "scenetree.h"
#include "scenetreenode.h"

namespace mr::qnage
{
    SceneTreeNode::SceneTreeNode(nage::SceneNode* _sceneNode, SceneTree* _parent)
        : QTreeWidgetItem(_parent),
          sceneNode_(_sceneNode)
    {
        QString nodeName = QString::fromStdString(_sceneNode->name());
        this->setText(0, nodeName.replace(0, 1, nodeName.at(0).toUpper()));
    }

    QString SceneTreeNode::name() const
    {
        return QString::fromStdString(sceneNode_->name());
    }

    void SceneTreeNode::addItem(nage::RenderableObject* _object)
    {
        if(!isChildItemExist(QString::fromStdString(_object->id())))
        {
            auto item = new RenderableSceneTreeNodeItem(_object, this);
            addChild(item);
        }
    }

    void SceneTreeNode::addCamera(nage::Camera* _camera)
    {
        auto item = new CameraSceneTreeNodeItem(_camera, this);
        addChild(item);
    }

    void SceneTreeNode::removeItem()
    {
        if(auto nodeItemOpt = activeChild(); nodeItemOpt.has_value())
        {
            auto nodeItem = nodeItemOpt.value();
            sceneNode_->removeFromScene(nodeItem->text(0).toStdString());

            delete nodeItem;
        }
    }

    std::optional<QTreeWidgetItem*> SceneTreeNode::activeChild()
    {
        for(int i = 0; i < childCount(); i++)
        {
            if(auto item = child(i); item)
            {
                if(item->isSelected())
                    return std::optional<QTreeWidgetItem*>{ item };
            }
        }

        return std::nullopt;
    }

    bool SceneTreeNode::isChildItemExist(const QString _itemName)
    {
        for(int i = 0; i < childCount(); i++)
        {
            if(auto item = child(i); item)
            {
                if(item->text(0) == _itemName)
                    return true;
            }
        }

        return false;
    }
}
