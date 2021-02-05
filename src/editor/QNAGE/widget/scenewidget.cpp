#include <QPalette>
#include "scenewidget.h"

namespace mr::qnage
{
    SceneWidget::SceneWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        this->setObjectName("scene-widget");
        this->setMinimumHeight(100);

        setupUi();
    }

    SceneWidget::~SceneWidget()
    {
        delete sceneTree_;
        delete scrollArea_;
        delete mainLayout_;
    }

    void SceneWidget::setupUi()
    {
        this->mainLayout_ = new QVBoxLayout;
        this->mainLayout_->setContentsMargins(10, 20, 10, 20);

        this->scrollArea_ = new QScrollArea(this);
        this->scrollArea_->setContentsMargins(0, 0, 0, 0);
        this->scrollArea_->setLayout(new QVBoxLayout);
        this->scrollArea_->setStyleSheet("QScrollArea { background: transparent; }");
        this->mainLayout_->addWidget(this->scrollArea_);

        this->sceneTree_ = new SceneTree(this);
        this->scrollArea_->layout()->addWidget(this->sceneTree_);
        connect(this->sceneTree_, &SceneTree::transformationsForNode, this, &SceneWidget::showTransformationSection);

        this->setLayout(this->mainLayout_);
    }

    SceneTree* SceneWidget::sceneTree()
    {
        return sceneTree_;
    }

    void SceneWidget::showTransformationSection(SceneTreeNodeItemTransformations* transformations)
    {
        int childCount = this->scrollArea_->layout()->count();
        if(childCount > 1)
        {
            for(int i = 1; i < childCount; ++i)
            {
                QLayoutItem* item = this->scrollArea_->layout()->itemAt(i);
                item->widget()->hide();
            }
        }

        if(notFoundWidget(transformations))
            this->scrollArea_->layout()->addWidget(transformations);

        transformations->show();
    }

    bool SceneWidget::notFoundWidget(QWidget* _widget)
    {
        QLayout* layout = this->scrollArea_->layout();
        for(int i = 0; i < layout->count(); ++i)
        {
            if(layout->itemAt(i)->widget() == _widget)
                return false;
        }

        return true;
    }
}
