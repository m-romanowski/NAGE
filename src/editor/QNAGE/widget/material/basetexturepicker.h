#ifndef QNAGE_WIDGET_MATERIAL_TEXTURE_BASETEXTUREPICKER_H_
#define QNAGE_WIDGET_MATERIAL_TEXTURE_BASETEXTUREPICKER_H_

#include "editor/QNAGE/dialog/dialog.h"
#include "editor/QNAGE/ui/clickablelabel.h"

namespace mr::qnage
{
    class BaseTexturePicker
        : public ClickableLabel
    {
        Q_OBJECT

    public:
        static constexpr const QSize DEFAULT_PICKER_AREA_SIZE = QSize(80, 80);

        explicit BaseTexturePicker(QWidget* _parent = nullptr, QSize _pickerAreaSize = DEFAULT_PICKER_AREA_SIZE);
        ~BaseTexturePicker();

        QImage* image() const;

    signals:
        void done();

    protected slots:
        void onClicked();

    protected:
        const QSize pickerAreaSize_;
        QImage* texture_;
        std::unique_ptr<Dialog> dialog_;
    };
}

#endif // QNAGE_WIDGET_MATERIAL_TEXTURE_BASETEXTUREPICKER_H_
