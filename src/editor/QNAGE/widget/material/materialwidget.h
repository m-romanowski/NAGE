#ifndef QNAGE_WIDGET_MATERIAL_MATERIALWIDGET_H_
#define QNAGE_WIDGET_MATERIAL_MATERIALWIDGET_H_

#include "editor/QNAGE/ui/headerbar.h"
#include "texture/texturepicker.h"
#include "heapmap/heapmapmaterial.h"

#include <QVBoxLayout>

namespace mr::qnage
{
    class MaterialWidget
        : public QWidget
    {
    public:
        explicit MaterialWidget(QWidget* _parent = nullptr);
        ~MaterialWidget();

    private:
        void setupUi();

        QVBoxLayout* mainLayout_;
        HeaderBar* widgetHeaderBar_;
        TexturePicker* texturePicker_;
        HeapmapMaterial* heapmapMaterial_;

        QSpacerItem* spacerItem_;
    };
}

#endif // QNAGE_WIDGET_MATERIAL_MATERIALWIDGET_H_
