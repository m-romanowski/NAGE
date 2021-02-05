#include "texturepicker.h"

#include <QDebug>

namespace mr::qnage
{
    TexturePicker::TexturePicker(QWidget* _parent, QSize _pickerAreaSize)
        : ClickableLabel(_parent)
    {
        this->setObjectName("texture-picker");
        this->setFixedSize(_pickerAreaSize);
        this->setPixmap(QPixmap(":/rc/icons/no-image.png").scaled(_pickerAreaSize));

        this->dialog_ = std::make_unique<TexturePickerDialog>();
    
        connect(this, &TexturePicker::clicked, this, &TexturePicker::onClicked);
    }

    void TexturePicker::onClicked()
    {
        if(this->dialog_->isVisible())
            return;

        this->dialog_->show();
    }
}
