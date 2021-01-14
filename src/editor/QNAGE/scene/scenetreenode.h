#ifndef QNAGE_SCENE_SCENETREENODE_H_
#define QNAGE_SCENE_SCENETREENODE_H_

#include "engine/core/scene/scenenode.h"
#include "scenetreenodeitem.h"

#include <QTreeWidgetItem>
#include <vector>
#include <optional>

namespace mr::qnage
{
    class SceneTree;

    class SceneTreeNode
        : public QTreeWidgetItem
    {
    public:
        SceneTreeNode(nage::SceneNode* _sceneNode, SceneTree* _parent = nullptr);

        QString name() const;

        void addItem(nage::RenderableObject* _object);
        void addCamera(nage::Camera* _camera);
        void removeItem();

    private:
        std::optional<QTreeWidgetItem*> activeChild();
        bool isChildItemExist(const QString _itemName);

        nage::SceneNode* sceneNode_;
    };
}

#endif // QNAGE_SCENE_SCENETREENODE_H_
