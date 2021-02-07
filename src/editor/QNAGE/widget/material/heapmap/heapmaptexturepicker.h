#ifndef QNAGE_WIDGET_MATERIAL_HEAPMAP_HEAPMAPTEXTUREPICKER_H_
#define QNAGE_WIDGET_MATERIAL_HEAPMAP_HEAPMAPTEXTUREPICKER_H_

#include "editor/QNAGE/widget/material/basetexturepicker.h"
#include "heapmapcreator.h"

namespace mr::qnage
{
    class HeapmapTexturePicker
        : public BaseTexturePicker
    {
        Q_OBJECT

    public:
        explicit HeapmapTexturePicker(QWidget* _parent = nullptr, QSize _pickerAreaSize = DEFAULT_PICKER_AREA_SIZE);

        QMap<HeapMapColor, QImage> heapmapDefinition() const;

    private:
        QMap<HeapMapColor, QImage> heapmapDefinitions_;
    };
}

#endif // QNAGE_WIDGET_MATERIAL_HEAPMAP_HEAPMAPTEXTUREPICKER_H_
