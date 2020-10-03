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

namespace mr::qnage
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
        inline MainWindow* getMainWindow() const { return mainWindow_; }
        inline GLWidget* getGLWidget() const { return glWidget_; }
        inline VKWidget* getVKWidget() const { return vkWidget_; }
        inline QString getWindowTitle() const { return windowTitle_; }
        inline bool isWindowDocked() const { return isDocked_; }

        // Setters
        void setMainWindow(MainWindow* _mainWindow) { mainWindow_ = _mainWindow; }
        void setGLWidget(GLWidget* _glWidget) { glWidget_ = _glWidget; reloadUi(); }
        void setVKWidget(VKWidget* _vkWidget) { vkWidget_ = _vkWidget; }
        void setEngineWindowTitle(const QString& _title);
        void setWindowDockProperty(bool _type) { isDocked_ = _type; }

        // Public methods
        void setupGLWidget(nage::IGame* _game);
        void reloadUi();

    signals:
        void rendererInitialized();

    private slots:
        void dockGLWindow();

    private:
        void setupUi();

        MainWindow* mainWindow_;
        GLWidget* glWidget_;
        VKWidget* vkWidget_;
        QString windowTitle_;

        // Ui
        bool isDocked_;

        QVBoxLayout* layout_;
        CustomButton* dockButton_;
    };
}

#endif // QNAGE_WINDOW_RENDERWINDOW_H_
