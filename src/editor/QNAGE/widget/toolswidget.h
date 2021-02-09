#ifndef QNAGE_WIDGET_TOOLSWIDGET_H_
#define QNAGE_WIDGET_TOOLSWIDGET_H_

#include "scenewidget.h"
#include "material/materialwidget.h"

#include <QVBoxLayout>

namespace mr::qnage
{
    class ToolsWidget
        : public QScrollArea
    {
        Q_OBJECT

    public:
        explicit ToolsWidget(QWidget* _parent = nullptr);
        ~ToolsWidget();

        SceneTree* sceneTree() { return this->sceneWidget_->sceneTree(); }

    private:
        void setupUi();
        void setupSceneTree();

        QWidget* childWidget_;
        QVBoxLayout* mainLayout_;
        SceneWidget* sceneWidget_;
        MaterialWidget* materialWidget_;
    };
}

#endif // QNAGE_WIDGET_TOOLSWIDGET_H_
