#ifndef QNAGE_UI_TEXTUREPICKER_H_
#define QNAGE_UI_TEXTUREPICKER_H_

#include "editor/QNAGE/ui/clickablelabel.h"
#include "texturepickerdialog.h"

namespace mr::qnage
{
    class TexturePicker
        : public ClickableLabel
    {
        static constexpr const QSize DEFAULT_PICKER_AREA_SIZE = QSize(80, 80);

    public:
        explicit TexturePicker(QWidget* _parent = nullptr, QSize _pickerAreaSize = DEFAULT_PICKER_AREA_SIZE);

    private slots:
        void onClicked();

    private:
        std::unique_ptr<TexturePickerDialog> dialog_;
    };
}

#endif // QNAGE_UI_TEXTUREPICKER_H_
