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
        inline RenderWindow* getRenderWindow() const { return renderWindow; }
        inline LogWidget* getDebugWindow() const { return logWidget; }

        // Setters
        void setRenderWindow(RenderWindow* _window);
        inline void setDebugWindow(LogWidget* _widget) { logWidget = _widget; }

        // Public methods
        void dockGLWindow();
        void undockGLWindow();

    private:
        void setupUi();

        // Editor components
        RenderWindow* renderWindow;
        LogWidget* logWidget;
        QWidget* toolsWidget;
        QWidget* workspaceWidget;

        // Ui
        QVBoxLayout* mainLayout;
        QVBoxLayout* workspaceLayout;

        QSplitter* verticalSplitter;
        QSplitter* horizontalSplitter;
    };
}

#endif // QNAGE_WIDGET_MAINWIDGET_H_
