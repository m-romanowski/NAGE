#ifndef QNAGE_WIDGET_MAINWIDGET_H_
#define QNAGE_WIDGET_MAINWIDGET_H_

#include "log/logwidget.h"
#include "window/renderwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>

namespace QNAGE
{
    class MainWidget : public QWidget
    {
    public:
        MainWidget(QWidget* _parent = nullptr);
        ~MainWidget();

        // Getters
        inline RenderWindow* getRenderWindow() const { return renderWindow_; }
        inline LogWidget* getDebugWindow() const { return logWidget_; }

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
        LogWidget* logWidget_;
        QWidget* toolsWidget_;
        QWidget* workspaceWidget_;

        // Ui
        QVBoxLayout* mainLayout_;
        QVBoxLayout* workspaceLayout_;

        QSplitter* verticalSplitter_;
        QSplitter* horizontalSplitter_;
    };
}

#endif // QNAGE_WIDGET_MAINWIDGET_H_
