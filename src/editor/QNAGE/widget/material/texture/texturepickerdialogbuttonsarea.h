#ifndef QNAGE_UI_TEXTUREPICKERDIALOGBUTTONSAREA_H_
#define QNAGE_UI_TEXTUREPICKERDIALOGBUTTONSAREA_H_

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>

namespace mr::qnage
{
    class TexturePickerDialogButtonsArea
        : public QWidget
    {
        Q_OBJECT

    public:
        explicit TexturePickerDialogButtonsArea(const QString _firstButtonText, const QString _secondButtonText, QWidget* _parent = nullptr)
            : QWidget(_parent)
        {
            this->buttonsLayout_ = new QHBoxLayout;
            this->setLayout(this->buttonsLayout_);

            this->buttonsSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            this->buttonsLayout_->addItem(this->buttonsSpacerItem_);

            this->firstButton_ = new QPushButton(this);
            this->buttonsLayout_->addWidget(this->firstButton_);
            this->firstButton_->setText(_firstButtonText);
            connect(this->firstButton_, &QPushButton::clicked, this, &TexturePickerDialogButtonsArea::firstButtonClicked);

            this->secondButton_ = new QPushButton(this);
            this->buttonsLayout_->addWidget(this->secondButton_);
            this->secondButton_->setText(_secondButtonText);
            connect(this->secondButton_, &QPushButton::clicked, this, &TexturePickerDialogButtonsArea::secondButonClicked);
        }

        ~TexturePickerDialogButtonsArea()
        {
            delete buttonsSpacerItem_;
            delete firstButton_;
            delete secondButton_;
            delete buttonsLayout_;
        }

        void enableFirst()
        {
            setButtonState(this->firstButton_, false);
        }

        void disableFirst()
        {
            setButtonState(this->firstButton_, false);
        }

        void enableSecond()
        {
            setButtonState(this->secondButton_, true);
        }

        void disableSecond()
        {
            setButtonState(this->secondButton_, false);
        }

    signals:
        void firstButtonClicked(bool _checked);
        void secondButonClicked(bool _checked);

    private:
        void setButtonState(QPushButton* _button, bool _state)
        {
            _button->setEnabled(_state);
        }

        QHBoxLayout* buttonsLayout_;
        QSpacerItem* buttonsSpacerItem_;
        QPushButton *firstButton_, *secondButton_; 
    };
}

#endif // QNAGE_UI_TEXTUREPICKERDIALOGBUTTONSAREA_H_
