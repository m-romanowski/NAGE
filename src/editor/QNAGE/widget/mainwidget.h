#ifndef QNAGE_WIDGET_MAINWIDGET_H_
#define QNAGE_WIDGET_MAINWIDGET_H_

#include "workspacewidget.h"
#include "scenewidget.h"
#include "log/logwidget.h"
#include "window/renderwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>

namespace mr::qnage
{
    class MainWidget : public QWidget
    {
    public:
        MainWidget(QWidget* _parent = nullptr);
        ~MainWidget();

        // Getters
        inline RenderWindow* renderWindow() const { return renderWindow_; }
        inline SceneWidget* sceneWidget() const { return sceneWidget_; }
        inline LogWidget* debugWindow() const { return logWidget_; }

        // Setters
        void setRenderWindow(RenderWindow* _window);
        inline void setDebugWindow(LogWidget* _widget) { logWidget_ = _widget; }

        // Public methods
        void dockGLWindow();
        void undockGLWindow();

    private:
        void setupUi();

        // Editor components
        RenderWindow* renderWindow_;
        SceneWidget* sceneWidget_;
        LogWidget* logWidget_;
        WorkspaceWidget* toolsWidget_;
        QWidget* workspaceWidget_;

        // Ui
        QVBoxLayout* mainLayout_;
        QVBoxLayout* workspaceLayout_;

        QSplitter* verticalSplitter_;
        QSplitter* horizontalSplitter_;
    };
}

#endif // QNAGE_WIDGET_MAINWIDGET_H_
