#include "workspacewidget.h"

namespace mr::qnage
{
    WorkspaceWidget::WorkspaceWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        setupUi();
    }

    WorkspaceWidget::~WorkspaceWidget()
    {
        delete sceneTree_;
        delete mainLayout_;
    }

    void WorkspaceWidget::setupUi()
    {
        if(!mainLayout_)
        {
            mainLayout_ = new QVBoxLayout;
            this->setLayout(mainLayout_);

            setupSceneTree();
        }
    }

    void WorkspaceWidget::setupSceneTree()
    {
        if(mainLayout_)
        {
            sceneTree_ = new SceneTree(this);
            mainLayout_->addWidget(sceneTree_);
        }
    }
}
