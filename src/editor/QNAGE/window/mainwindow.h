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

// Debugger
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

namespace QNAGE
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(int _width = 800, int _height = 600);
        virtual ~MainWindow();

        // Getters
        inline int getWidth() const { return width; }
        inline int getHeight() const { return height; }
        inline QSize getSize() const { return QSize(width, height); }

        // Setters
        inline void setWidth(int _width) { width = _width; }
        inline void setHeight(int _height) { height = _height; }
        inline void setSize(QSize _size) { width = _size.width(); height = _size.height(); }

        void addWindow(RenderWindow* _window);
        bool isEngineWindow() const { return this->mainWidget->getRenderWindow() == nullptr ? true : false; }
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
        ProjectDialog* projectDialog;

        // MainWindow Ui
        int width;
        int height;
        bool isMoving;
        QPoint lastMousePosition;

        MainWidget* mainWidget;
        WelcomeWidget* welcomeWidget;
        SettingsWidget* settingsWidget;
        QWidget* centralWidget;
        QWidget* windowTitleWidget;

        QVBoxLayout* windowLayout;
        QGridLayout* topLayout;
        TabWidget* tabWidget;

        CustomButton* exitButton;
        CustomButton* minimizeButton;
        CustomButton* maximizeButton;

        QToolButton* runButton;
        QToolButton* buildButton;

        // Menubar
        QMenuBar* menuBar;
        QMenu* projectMenu;
        QMenu* editMenu;
        QMenu* buildMenu;
        QMenu* settingsMenu;

        QAction* openProjectDialogAction;
        QAction* openSettingDialogAction;
    };
}

#endif // QNAGE_WINDOW_MAINWINDOW_H_
