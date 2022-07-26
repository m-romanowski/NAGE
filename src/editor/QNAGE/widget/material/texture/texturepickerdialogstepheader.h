#ifndef QNAGE_WIDGET_MATERIAL_TEXTURE_TEXTUREPICKERDIALOGSTEPHEADER_H_
#define QNAGE_WIDGET_MATERIAL_TEXTURE_TEXTUREPICKERDIALOGSTEPHEADER_H_

#include <QLabel>

namespace mr::qnage
{
    class TexturePickerDialogStepHeader
        : public QLabel
    {
        Q_OBJECT

    public:
        explicit TexturePickerDialogStepHeader(QString _title, QWidget* _parent = nullptr)
            : QLabel(_parent)
        {
            this->setText(_title);
            this->setObjectName("texture-picker-dialog-step-header");
        }
    };
}


#endif // QNAGE_WIDGET_MATERIAL_TEXTURE_TEXTUREPICKERDIALOGSTEPHEADER_H_
