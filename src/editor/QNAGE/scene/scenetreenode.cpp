#include "scenetree.h"
#include "scenetreenode.h"

namespace mr::qnage
{
    SceneTreeNode::SceneTreeNode(ISceneNode* _sceneNode, SceneTree* _parent)
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

    void SceneTreeNode::addItem(ISceneObject* _object)
    {
        if(!isChildItemExist(QString::fromStdString(_object->id())))
        {
            SceneTreeNodeItemTransformations::Type transformType = 
                _object->transformation()->isAvailable()
                    ? SceneTreeNodeItem::ALL_TRANSFORMATIONS
                    : SceneTreeNodeItemTransformations::Type::None;

            auto item = new SceneTreeNodeItem(SceneTreeNodeItem::Type::Model, _object, transformType, this);
            addChild(item);
        }
    }

    void SceneTreeNode::addCamera(ICamera* _camera, bool _select)
    {
        auto item = new SceneTreeNodeItem(_camera, this);
        item->setSelected(_select);
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
