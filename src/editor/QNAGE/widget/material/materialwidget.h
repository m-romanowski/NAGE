#ifndef QNAGE_WIDGET_MATERIAL_MATERIALWIDGET_H_
#define QNAGE_WIDGET_MATERIAL_MATERIALWIDGET_H_

#include "editor/QNAGE/interface/isceneresource.h"
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

        void setResourceHandler(ISceneResource* _resource);

    private:
        void setupUi();

        ISceneResource* resourceHandler_;

        QVBoxLayout* mainLayout_;
        HeaderBar* widgetHeaderBar_;
        TexturePicker* texturePicker_;
        HeapmapMaterial* heapmapMaterial_;

        QSpacerItem* spacerItem_;
    };
}

#endif // QNAGE_WIDGET_MATERIAL_MATERIALWIDGET_H_
