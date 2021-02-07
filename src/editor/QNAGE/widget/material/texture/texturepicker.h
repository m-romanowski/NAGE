#ifndef QNAGE_WIDGET_MATERIAL_TEXTURE_TEXTUREPICKER_H_
#define QNAGE_WIDGET_MATERIAL_TEXTURE_TEXTUREPICKER_H_

#include "editor/QNAGE/widget/material/basetexturepicker.h"
#include "texturepickerdialog.h"

namespace mr::qnage
{
    class TexturePicker
        : public BaseTexturePicker
    {
        Q_OBJECT

    public:
        explicit TexturePicker(QWidget* _parent = nullptr, QSize _pickerAreaSize = DEFAULT_PICKER_AREA_SIZE);
    };
}

#endif // QNAGE_WIDGET_MATERIAL_TEXTURE_TEXTUREPICKER_H_
