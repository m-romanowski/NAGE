#ifndef QNAGE_SCENE_SCENETREENODEITEMTRANSFORMATIONS_H_
#define QNAGE_SCENE_SCENETREENODEITEMTRANSFORMATIONS_H_

#include "ui/decimallineedit.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QRegExpValidator>

namespace mr::qnage
{
    class SceneEditableTransformationWidget
        : public QWidget
    {
        Q_OBJECT

    public:
        SceneEditableTransformationWidget(const QString _label, QWidget* _parent = nullptr)
            : QWidget(_parent)
        {
            this->mainLayout_ = new QVBoxLayout;

            this->widgetLabel_ = new QLabel(_label, this);
            this->mainLayout_->addWidget(this->widgetLabel_);

            this->editableLayout_ = new QHBoxLayout;
            this->mainLayout_->addLayout(this->editableLayout_);

            this->editableX_ = new DecimalLineEdit("x", this);
            this->editableLayout_->addWidget(this->editableX_);

            this->editableY_ = new DecimalLineEdit("y", this);
            this->editableLayout_->addWidget(this->editableY_);

            this->editableZ_ = new DecimalLineEdit("z", this);
            this->editableLayout_->addWidget(this->editableZ_);

            this->setLayout(this->mainLayout_);
        }

        ~SceneEditableTransformationWidget()
        {
            delete widgetLabel_;
            delete editableX_;
            delete editableY_;
            delete editableZ_;
            delete editableLayout_;
            delete mainLayout_;
        }

    signals:
        void onChange();

    private:
        QVBoxLayout* mainLayout_;
        QHBoxLayout* editableLayout_;

        QLabel* widgetLabel_;
        DecimalLineEdit *editableX_, *editableY_, *editableZ_;
    };

    class SceneTreeNodeItemTransformations
        : public QWidget
    {
        Q_OBJECT

    public:
        explicit SceneTreeNodeItemTransformations(QWidget* _parent = nullptr);
        ~SceneTreeNodeItemTransformations();

    private:
        void setupUi();

        QVBoxLayout* mainLayout_;

        // Widget label
        QLabel* widgetLabel_;

        // Translation
        SceneEditableTransformationWidget* translationWidget_;

        // Rotation
        SceneEditableTransformationWidget* rotationWidget_;

        // Scaling
        SceneEditableTransformationWidget* scalingWidget_;

        // Shearing
        SceneEditableTransformationWidget* shearingWidget_;
    };
}

#endif // QNAGE_SCENE_SCENETREENODEITEMTRANSFORMATIONS_H_
