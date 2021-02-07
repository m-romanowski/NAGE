#include "texturepicker.h"

namespace mr::qnage
{
    TexturePicker::TexturePicker(QWidget* _parent, QSize _pickerAreaSize)
        : ClickableLabel(_parent),
          pickerAreaSize_(_pickerAreaSize),
          texture_(nullptr)
    {
        this->setObjectName("texture-picker");
        this->setFixedSize(_pickerAreaSize);
        this->setPixmap(QPixmap(":/rc/icons/no-image.png").scaled(_pickerAreaSize));

        this->dialog_ = std::make_unique<TexturePickerDialog>();
        connect(this->dialog_.get(), &TexturePickerDialog::textureSelected, [this](QImage _image) {
            delete texture_;
            texture_ = new QImage(_image);
            this->setPixmap(QPixmap::fromImage(*texture_).scaled(this->pickerAreaSize_));
            this->dialog_->close();
        });

        connect(this, &TexturePicker::clicked, this, &TexturePicker::onClicked);
    }

    TexturePicker::~TexturePicker()
    {
        delete texture_;
    }

    void TexturePicker::onClicked()
    {
        if(this->dialog_->isVisible())
            return;

        this->dialog_->show();
    }
}
