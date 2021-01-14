#ifndef QNAGE_WIDGET_SCENEWIDGET_H_
#define QNAGE_WIDGET_SCENEWIDGET_H_

#include "scene/scenetree.h"
#include "scene/scenetreenodeitemtransformations.h"

#include <QVBoxLayout>
#include <QScrollArea>

namespace mr::qnage
{
    class SceneWidget
        : public QScrollArea
    {
        Q_OBJECT

    public:
        explicit SceneWidget(QWidget* _parent = nullptr);
        ~SceneWidget();

        SceneTree* sceneTree();

    private:
        void setupUi();

        QVBoxLayout* mainLayout_;
        SceneTree* sceneTree_;
        SceneTreeNodeItemTransformations* sceneTreeNodeItemTransformations_;
    };
}

#endif // QNAGE_WIDGET_SCENEWIDGET_H_
