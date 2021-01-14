#include "scenewidget.h"

namespace mr::qnage
{
    SceneWidget::SceneWidget(QWidget* _parent)
        : QScrollArea(_parent)
    {
        this->setObjectName("scene-widget");

        setupUi();
    }

    SceneWidget::~SceneWidget()
    {
        delete sceneTree_;
        delete sceneTreeNodeItemTransformations_;
        delete mainLayout_;
    }

    void SceneWidget::setupUi()
    {
        this->mainLayout_ = new QVBoxLayout;
        this->mainLayout_->setContentsMargins(10, 20, 10, 20);

        this->sceneTree_ = new SceneTree(this);
        this->mainLayout_->addWidget(this->sceneTree_);

        this->sceneTreeNodeItemTransformations_ = new SceneTreeNodeItemTransformations(this);
        this->mainLayout_->addWidget(this->sceneTreeNodeItemTransformations_);

        this->setLayout(this->mainLayout_);
    }

    SceneTree* SceneWidget::sceneTree()
    {
        return sceneTree_;
    }
}
