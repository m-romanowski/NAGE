#include "texturepicker.h"

namespace mr::qnage
{
    TexturePicker::TexturePicker(QWidget* _parent, QSize _pickerAreaSize)
        : BaseTexturePicker(_parent, _pickerAreaSize)
    {
        this->dialog_ = std::make_unique<TexturePickerDialog>();
        connect(reinterpret_cast<TexturePickerDialog*>(this->dialog_.get()), &TexturePickerDialog::textureSelected, [this](QImage _image) {
            delete texture_;
            this->texture_ = new QImage(_image);
            this->setPixmap(QPixmap::fromImage(*texture_).scaled(this->pickerAreaSize_));

            emit done();
            this->dialog_->close();
        });
    }
}
