#include <cmath>
#include "scenetreenodeitemtransformations.h"

namespace mr::qnage
{
    SceneTreeNodeItemTransformations::SceneTreeNodeItemTransformations(Type type, QWidget* _parent)
        : QWidget(_parent),
          widgetLabel_(nullptr),
          translationWidget_(nullptr),
          rotationWidget_(nullptr),
          scalingWidget_(nullptr),
          shearingWidget_(nullptr),
          mainLayout_(nullptr)
    {
        setupUi(type);
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

    void SceneTreeNodeItemTransformations::setupUi(Type type)
    {
        if(type == Type::None)
            return;

        this->mainLayout_ = new QVBoxLayout;
        this->mainLayout_->setMargin(0);
        this->setContentsMargins(0, 0, 0, 0);

        this->widgetLabel_ = new HeaderBar("Transformations", this);
        this->mainLayout_->addWidget(this->widgetLabel_);

        if((type & Type::Translation) == Type::Translation)
        {
            this->translationWidget_ = new SceneEditableTransformationWidget("Translation", this);
            this->translationWidget_->setEnabled(false); // TODO: re-enable after editing fix
            connect(this->translationWidget_, &SceneEditableTransformationWidget::onChange, this,
                &SceneTreeNodeItemTransformations::onTranslation);
            this->mainLayout_->addWidget(this->translationWidget_);
        }

        if((type & Type::Rotation) == Type::Rotation)
        {
            this->rotationWidget_ = new SceneEditableTransformationWidget("Rotation", this);
            this->rotationWidget_->setEnabled(false); // TODO: re-enable after editing fix
            connect(this->rotationWidget_, &SceneEditableTransformationWidget::onChange, this,
                &SceneTreeNodeItemTransformations::onRotation);
            this->mainLayout_->addWidget(this->rotationWidget_);
        }

        if((type & Type::Scaling) == Type::Scaling)
        {
            this->scalingWidget_ = new SceneEditableTransformationWidget("Scaling", this);
            this->scalingWidget_->setEnabled(false); // TODO: re-enable after editing fix
            connect(this->scalingWidget_, &SceneEditableTransformationWidget::onChange, this,
                &SceneTreeNodeItemTransformations::onScaling);
            this->mainLayout_->addWidget(this->scalingWidget_);
        }

        if((type & Type::Shearing) == Type::Shearing)
        {
            this->shearingWidget_ = new SceneEditableTransformationWidget("Shearing", this);
            this->shearingWidget_->setEnabled(false); // TODO: re-enable after editing fix
            connect(this->shearingWidget_, &SceneEditableTransformationWidget::onChange, this,
                &SceneTreeNodeItemTransformations::onShearing);
            this->mainLayout_->addWidget(this->shearingWidget_);
        }

        this->setLayout(this->mainLayout_);
    }

    void SceneTreeNodeItemTransformations::setTranslation(float x, float y, float z)
    {
        translationWidget_->setVec3(std::roundf(x), std::roundf(y), std::roundf(z));
    }

    void SceneTreeNodeItemTransformations::setRotation(float x, float y, float z)
    {
        rotationWidget_->setVec3(std::roundf(x), std::roundf(y), std::roundf(z));
    }

    void SceneTreeNodeItemTransformations::setScaling(float x, float y, float z)
    {
        scalingWidget_->setVec3(std::roundf(x), std::roundf(y), std::roundf(z));
    }

    void SceneTreeNodeItemTransformations::setShearing(float x, float y, float z)
    {
        shearingWidget_->setVec3(std::roundf(x), std::roundf(y), std::roundf(z));
    }
}
