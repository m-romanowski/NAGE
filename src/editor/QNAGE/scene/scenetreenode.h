#ifndef QNAGE_SCENE_SCENETREENODE_H_
#define QNAGE_SCENE_SCENETREENODE_H_

#include "interface/iscenenode.h"
#include "interface/isceneobject.h"
#include "scenetreenodeitem.h"

#include <vector>
#include <optional>
#include <QTreeWidgetItem>

namespace mr::qnage
{
    class SceneTree;

    class SceneTreeNode
        : public QTreeWidgetItem
    {
    public:
        SceneTreeNode(ISceneNode* _sceneNode, SceneTree* _parent = nullptr);

        QString name() const;

        void addItem(ISceneObject* _object);
        void addCamera(ICamera* _camera, bool _select = true);
        void removeItem();
        std::optional<QTreeWidgetItem*> activeChild();

    private:
        bool isChildItemExist(const QString _itemName);

        ISceneNode* sceneNode_;
    };
}

#endif // QNAGE_SCENE_SCENETREENODE_H_
