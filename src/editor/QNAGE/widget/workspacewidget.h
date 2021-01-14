#ifndef QNAGE_WIDGET_WORKSPACEWIDGET_H_
#define QNAGE_WIDGET_WORKSPACEWIDGET_H_

#include "scene/scenetree.h"

#include <QVBoxLayout>

namespace mr::qnage
{
    class WorkspaceWidget
        : public QWidget
    {
        Q_OBJECT

    public:
        explicit WorkspaceWidget(QWidget* _parent = nullptr);
        ~WorkspaceWidget();

    private:
        void setupUi();
        void setupSceneTree();

        QVBoxLayout* mainLayout_;
        SceneTree* sceneTree_;
    };
}

#endif // QNAGE_WIDGET_WORKSPACEWIDGET_H_
