#include "scenetreenodeitemtransformations.h"

namespace mr::qnage
{
    SceneTreeNodeItemTransformations::SceneTreeNodeItemTransformations(QWidget* _parent)
        : QWidget(_parent)
    {
        setupUi();
    }

    SceneTreeNodeItemTransformations::~SceneTreeNodeItemTransformations()
    {
        delete widgetLabel_;
        delete translationWidget_;
        delete rotationWidget_;
        delete scalingWidget_;
        delete shearingWidget_;
        delete mainLayout_;
    }

    void SceneTreeNodeItemTransformations::setupUi()
    {
        this->mainLayout_ = new QVBoxLayout;
        this->mainLayout_->setMargin(0);
        this->setContentsMargins(0, 0, 0, 0);

        this->widgetLabel_ = new QLabel("Transformations", this);
        this->widgetLabel_->setObjectName("scene-tree-node-item-transformations-label");
        this->mainLayout_->addWidget(this->widgetLabel_);

        this->translationWidget_ = new SceneEditableTransformationWidget("Translation", this);
        this->mainLayout_->addWidget(this->translationWidget_);

        this->rotationWidget_ = new SceneEditableTransformationWidget("Rotation", this);
        this->mainLayout_->addWidget(this->rotationWidget_);

        this->scalingWidget_ = new SceneEditableTransformationWidget("Scaling", this);
        this->mainLayout_->addWidget(this->scalingWidget_);

        this->shearingWidget_ = new SceneEditableTransformationWidget("Shearing", this);
        this->mainLayout_->addWidget(this->shearingWidget_);

        this->setLayout(this->mainLayout_);
    }
}
