#ifndef QNAGE_SCENE_SCENETREENODEITEMTRANSFORMATIONS_H_
#define QNAGE_SCENE_SCENETREENODEITEMTRANSFORMATIONS_H_

#include "ui/decimallineedit.h"
#include "ui/headerbar.h"

#include <type_traits>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QToolButton>
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
            connect(this->editableX_, &DecimalLineEdit::textEdited, this, &SceneEditableTransformationWidget::emitChange);
            this->editableLayout_->addWidget(this->editableX_);

            this->editableY_ = new DecimalLineEdit("y", this);
            connect(this->editableY_, &DecimalLineEdit::textEdited, this, &SceneEditableTransformationWidget::emitChange);
            this->editableLayout_->addWidget(this->editableY_);

            this->editableZ_ = new DecimalLineEdit("z", this);
            connect(this->editableZ_, &DecimalLineEdit::textEdited, this, &SceneEditableTransformationWidget::emitChange);
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

        void setVec3(float x, float y , float z)
        {
            setX(x);
            setY(y);
            setZ(z);
        }

        void setX(float x)
        {
            editableX_->set(x);
        }

        void setY(float y)
        {
            editableY_->set(y);
        }

        void setZ(float z)
        {
            editableZ_->set(z); 
        }

    signals:
        void onChange(float x, float y, float z);

    private:
        void emitChange(const QString& ignore)
        {
            emit onChange(
                this->editableX_->text().toInt(),
                this->editableY_->text().toInt(),
                this->editableZ_->text().toInt()
            );
        }

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
        enum class Type
        {
            None = -1,
            Translation,
            Rotation,
            Scaling,
            Shearing
        };

    public:
        explicit SceneTreeNodeItemTransformations(Type type, QWidget* _parent = nullptr);
        ~SceneTreeNodeItemTransformations();

        void setTranslation(float x, float y, float z);
        void setRotation(float x, float y, float z);
        void setScaling(float x, float y, float z);
        void setShearing(float x, float y, float z);

    signals:
        void onTranslation(float x, float y, float z);
        void onRotation(float x, float y, float z);
        void onScaling(float x, float y, float z);
        void onShearing(float x, float y, float z);

    private:
        void setupUi(Type type);

        QVBoxLayout* mainLayout_;

        // Widget label
        HeaderBar* widgetLabel_;

        // Translation
        SceneEditableTransformationWidget* translationWidget_;

        // Rotation
        SceneEditableTransformationWidget* rotationWidget_;

        // Scaling
        SceneEditableTransformationWidget* scalingWidget_;

        // Shearing
        SceneEditableTransformationWidget* shearingWidget_;
    };

    inline constexpr SceneTreeNodeItemTransformations::Type operator|(SceneTreeNodeItemTransformations::Type lhs,
        SceneTreeNodeItemTransformations::Type rhs)
    {
        using T = std::underlying_type_t <SceneTreeNodeItemTransformations::Type>;
        return static_cast<SceneTreeNodeItemTransformations::Type>(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    inline constexpr SceneTreeNodeItemTransformations::Type operator&(SceneTreeNodeItemTransformations::Type lhs,
        SceneTreeNodeItemTransformations::Type rhs)
    {
        using T = std::underlying_type_t <SceneTreeNodeItemTransformations::Type>;
        return static_cast<SceneTreeNodeItemTransformations::Type>(static_cast<T>(lhs) & static_cast<T>(rhs));
    }
}

#endif // QNAGE_SCENE_SCENETREENODEITEMTRANSFORMATIONS_H_
