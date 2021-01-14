#ifndef QNAGE_SCENE_SCENETREE_H_
#define QNAGE_SCENE_SCENETREE_H_

#include "engine/core/scene/scenemanager.h"
#include "scenetreenode.h"

#include <QTreeWidget>
#include <vector>
#include <optional>

namespace mr::qnage
{
    class SceneTree
        : public QTreeWidget
    {
        Q_OBJECT

    public:
        explicit SceneTree(QWidget* _parent = nullptr);

        void setSceneHandler(nage::SceneManager* _sceneManager);
        void addScene(const QString _sceneName);
        void removeScene();

    private:
        SceneTreeNode* addToTree(nage::SceneNode* _sceneNode);
        std::optional<SceneTreeNode*> activeChildNode();
        bool isChildNodeExist(const QString _sceneName);

        nage::SceneManager* sceneManager_;
    };
}

#endif // QNAGE_SCENE_SCENETREE_H_
