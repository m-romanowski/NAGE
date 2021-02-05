#ifndef QNAGE_WIDGET_SCENEWIDGET_H_
#define QNAGE_WIDGET_SCENEWIDGET_H_

#include "scene/scenetree.h"
#include "scene/scenetreenodeitemtransformations.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QSplitter>

namespace mr::qnage
{
    class SceneWidget
        : public QWidget
    {
        Q_OBJECT

    public:
        explicit SceneWidget(QWidget* _parent = nullptr);
        ~SceneWidget();

        SceneTree* sceneTree();

    private slots:
        void showTransformationSection(SceneTreeNodeItemTransformations* transformations);

    private:
        void setupUi();
        bool notFoundWidget(QWidget* _widget);

        QScrollArea* scrollArea_;
        QVBoxLayout* mainLayout_;
        SceneTree* sceneTree_;
    };
}

#endif // QNAGE_WIDGET_SCENEWIDGET_H_
