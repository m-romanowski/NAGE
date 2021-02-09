#include "toolswidget.h"
namespace mr::qnage
{
    ToolsWidget::ToolsWidget(QWidget* _parent)
        : QScrollArea(_parent)
    {
        this->setWidgetResizable(true);
        this->setStyleSheet("QScrollArea { background: transparent; }");
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
        this->childWidget_ = new QWidget(this);
        this->childWidget_->setObjectName("tool-widget-child");
        this->childWidget_->setStyleSheet("QWidget#tool-widget-child { background: transparent; }");
        this->mainLayout_ = new QVBoxLayout(this->childWidget_);
        this->childWidget_->setLayout(this->mainLayout_);
        this->setWidget(this->childWidget_);

        setupSceneTree();
    }

    void ToolsWidget::setupSceneTree()
    {
        this->sceneWidget_ = new SceneWidget(this);
        this->mainLayout_->addWidget(this->sceneWidget_);
        connect(this->sceneWidget_, &SceneWidget::selectedItemResource, [this](ISceneResource* _resource) {
            if(_resource && _resource->isNotEmpty())
            {
                this->materialWidget_->show();
                this->materialWidget_->setResourceHandler(_resource);
            }
            else
            {
                this->materialWidget_->hide();
            }
        });

        this->materialWidget_ = new MaterialWidget(this);
        this->materialWidget_->hide();
        this->mainLayout_->addWidget(this->materialWidget_);
    }
}
