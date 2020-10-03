#ifndef QNAGE_WINDOW_MAINWINDOW_H_
#define QNAGE_WINDOW_MAINWINDOW_H_

// OpenGL
#include "renderwindow.h"

// Ui
#include "ui/custombutton.h"
#include "ui/tabwidget.h"
#include "widget/glwidget.h"
#include "widget/mainwidget.h"
#include "widget/welcomewidget.h"
#include "widget/setingswidget.h"

// Logger
#include "log/logwidget.h"

// Dialog
#include "dialog/projectdialog.h"

// Engine
#include "engine/core/coreengine.h"
#include "game/game.h"

// QT
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QPoint>
#include <QSplitter>
#include <QSizeGrip>
#include <QList>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

namespace mr::qnage
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(int _width = 800, int _height = 600);
        virtual ~MainWindow();

        // Getters
        inline int getWidth() const { return width_; }
        inline int getHeight() const { return height_; }
        inline QSize getSize() const { return QSize(width_, height_); }

        // Setters
        inline void setWidth(int _width) { width_ = _width; }
        inline void setHeight(int _height) { height_ = _height; }
        inline void setSize(QSize _size) { width_ = _size.width(); height_ = _size.height(); }

        void addWindow(RenderWindow* _window);
        bool isEngineWindow() const { return this->mainWidget_->getRenderWindow() == nullptr ? true : false; }
        void dockEngineWindow();
        void undockEngineWindow();

    private slots:
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event);
        void onExitButtonClicked();
        void onMaximizeButtonClicked();
        void onMinimizeButtonClicked();
        void openSettingsDialog();
        void openProjectDialog();

    private:
        void init();
        void setupUi();
        void createMenus();
        void createActions();

        // Dialog
        ProjectDialog* projectDialog_;

        // MainWindow Ui
        int width_;
        int height_;
        bool isMoving_;
        QPoint lastMousePosition_;

        MainWidget* mainWidget_;
        WelcomeWidget* welcomeWidget_;
        SettingsWidget* settingsWidget_;
        QWidget* centralWidget_;
        QWidget* windowTitleWidget_;

        QVBoxLayout* windowLayout_;
        QGridLayout* topLayout_;
        TabWidget* tabWidget_;

        CustomButton* exitButton_;
        CustomButton* minimizeButton_;
        CustomButton* maximizeButton_;

        QToolButton* runButton_;
        QToolButton* buildButton_;

        // Menubar
        QMenuBar* menuBar_;
        QMenu* projectMenu_;
        QMenu* editMenu_;
        QMenu* buildMenu_;
        QMenu* settingsMenu_;

        QAction* openProjectDialogAction_;
        QAction* openSettingDialogAction_;
    };
}

#endif // QNAGE_WINDOW_MAINWINDOW_H_
