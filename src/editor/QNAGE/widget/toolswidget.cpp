#include "toolswidget.h"

namespace mr::qnage
{
    ToolsWidget::ToolsWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        setupUi();
    }

    ToolsWidget::~ToolsWidget()
    {
        delete sceneWidget_;
        delete materialWidget_;
        delete mainLayout_;
    }

    void ToolsWidget::setupUi()
    {
        this->mainLayout_ = new QVBoxLayout(this);
        this->setLayout(mainLayout_);

        setupSceneTree();
    }

    void ToolsWidget::setupSceneTree()
    {
        this->sceneWidget_ = new SceneWidget(this);
        this->mainLayout_->addWidget(this->sceneWidget_);

        this->materialWidget_ = new MaterialWidget(this);
        this->mainLayout_->addWidget(this->materialWidget_);
    }
}
