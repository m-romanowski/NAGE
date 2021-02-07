#include "basetexturepicker.h"

namespace mr::qnage
{
    BaseTexturePicker::BaseTexturePicker(QWidget* _parent, QSize _pickerAreaSize)
        : ClickableLabel(_parent),
          pickerAreaSize_(_pickerAreaSize),
          texture_(nullptr)
    {
        this->setObjectName("texture-picker");
        this->setFixedSize(_pickerAreaSize);
        this->setPixmap(QPixmap(":/rc/icons/no-image.png").scaled(_pickerAreaSize));

        connect(this, &BaseTexturePicker::clicked, this, &BaseTexturePicker::onClicked);
    }

    BaseTexturePicker::~BaseTexturePicker()
    {
        delete texture_;
    }

    QImage* BaseTexturePicker::image() const
    {
        return texture_;
    }

    void BaseTexturePicker::onClicked()
    {
        if(this->dialog_.get() && this->dialog_->isVisible())
            return;

        this->dialog_->show();
    }
}
