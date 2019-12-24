#ifndef QNAGE_WINDOW_RENDERWINDOW_H_
#define QNAGE_WINDOW_RENDERWINDOW_H_

#include "engine/core/igame.h"

// Widgets
#include "framelesswindow.h"
#include "ui/custombutton.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QIcon>
#include <QPoint>
#include <QCursor>

namespace QNAGE
{
    class MainWindow;
    class GLWidget;
    class VKWidget;
    class Bridge;

    class RenderWindow : public FramelessWindow
    {
        Q_OBJECT

    public:
        RenderWindow(MainWindow* _mainWindow);
        ~RenderWindow() override;

        // Getters
        inline MainWindow* getMainWindow() const { return mainWindow; }
        inline GLWidget* getGLWidget() const { return glWidget; }
        inline VKWidget* getVKWidget() const { return vkWidget; }
        inline QString getWindowTitle() const { return windowTitle; }
        inline bool isWindowDocked() const { return isDocked; }

        // Setters
        void setMainWindow(MainWindow* _mainWindow) { mainWindow = _mainWindow; }
        void setGLWidget(GLWidget* _glWidget) { glWidget = _glWidget; reloadUi(); }
        void setVKWidget(VKWidget* _vkWidget) { vkWidget = _vkWidget; }
        void setEngineWindowTitle(const QString& _title);
        void setWindowDockProperty(bool _type) { isDocked = _type; }

        // Public methods
        void setupGLWidget(NAGE::IGame* _game);
        void reloadUi();

    private slots:
        void dockGLWindow();

    private:
        void setupUi();

        MainWindow* mainWindow;
        GLWidget* glWidget;
        VKWidget* vkWidget;
        QString windowTitle;

        // Ui
        bool isDocked;

        QVBoxLayout* layout;
        CustomButton* dockButton;
    };
}

#endif // QNAGE_WINDOW_RENDERWINDOW_H_
