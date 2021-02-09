#ifndef QNAGE_SCENE_SCENETREE_H_
#define QNAGE_SCENE_SCENETREE_H_

#include "interface/iscenemanager.h"
#include "scenetreenode.h"

#include <vector>
#include <optional>
#include <QTreeWidget>

namespace mr::qnage
{
    class SceneTree
        : public QTreeWidget
    {
        Q_OBJECT

    public:
        explicit SceneTree(QWidget* _parent = nullptr);

        void setSceneHandler(ISceneManager* _sceneManager);
        void addScene(const QString _sceneName);
        void removeScene();

    signals:
        void onSelectedItem(ISceneTreeNodeItem* _sceneItem);

    private slots:
        void onClicked(QTreeWidgetItem* _item, int _column);

    private:
        SceneTreeNode* addToTree(ISceneNode* _sceneNode);
        std::optional<SceneTreeNode*> activeChildNode();
        bool isChildNodeExist(const QString _sceneName);

        ISceneManager* sceneManager_;
    };
}

#endif // QNAGE_SCENE_SCENETREE_H_
