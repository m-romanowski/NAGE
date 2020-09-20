#include "mainwindow.h"

namespace QNAGE
{
    MainWindow::MainWindow(int _width, int _height)
        : width_(_width),
          height_(_height),
          isMoving_(false),
          lastMousePosition_(QPoint(0, 0)),
          mainWidget_(new MainWidget),
          welcomeWidget_(new WelcomeWidget),
          settingsWidget_(new SettingsWidget)
    {
        this->setMinimumSize(width_, height_);
    }

    MainWindow::~MainWindow()
    {
        // Menus, Actions
        // delete openProjectDialogAction_;
        // delete openSettingDialogAction_;
        // delete settingsMenu_;
        // delete buildMenu_;
        // delete editMenu_;
        // delete projectMenu_;
        // delete menuBar_;

        // Buttons
        delete buildButton_;
        delete runButton_;
        delete exitButton_;
        delete minimizeButton_;
        delete maximizeButton_;

        // Widgets
        delete windowTitleWidget_;
        delete settingsWidget_;
        delete welcomeWidget_;
        delete mainWidget_;

        // Layouts, main window widgets.
        delete tabWidget_;
        delete topLayout_;
        delete windowLayout_;
        delete centralWidget_;
    }

    void MainWindow::init()
    {
        setupUi();
        // createActions();
        // createMenus();
    }

    void MainWindow::setupUi()
    {
        // Window settings
        this->setMouseTracking(true);
        this->setWindowFlags(Qt::FramelessWindowHint);

        // Central widget
        this->centralWidget_ = new QWidget(this);

        // Top layout
        this->topLayout_ = new QGridLayout();
        this->topLayout_->setContentsMargins(6, 6, 6, 6);

        this->windowTitleWidget_ = new QWidget(this->centralWidget_);
        this->windowTitleWidget_->setCursor(Qt::OpenHandCursor);
        this->topLayout_->addWidget(this->windowTitleWidget_, 0, 0, 1, 1);

        // Exit button
        this->exitButton_ = new CustomButton(this->centralWidget_);
        this->exitButton_->setCustomName("exit-btn");
        QIcon exitButtonIcon;
        exitButtonIcon.addPixmap(QPixmap(":/rc/icons/close.png"), QIcon::Normal, QIcon::Off);
        this->exitButton_->setCustomIcon(exitButtonIcon, QSize(23, 23));
        connect(this->exitButton_, &QPushButton::clicked, this, [this]{ this->onExitButtonClicked(); });
        this->topLayout_->addWidget(this->exitButton_, 0, 3, 1, 1);

        // Minimize button
        this->minimizeButton_ = new CustomButton(this->centralWidget_);
        this->minimizeButton_->setCustomName("dark-btn");
        QIcon minimizeButtonIcon;
        minimizeButtonIcon.addPixmap(QPixmap(":/rc/icons/minimize.png"), QIcon::Normal, QIcon::Off);
        this->minimizeButton_->setCustomIcon(minimizeButtonIcon, QSize(23, 23));
        connect(this->minimizeButton_, &QPushButton::clicked, this, [this]{ this->onMinimizeButtonClicked(); });
        this->topLayout_->addWidget(this->minimizeButton_, 0, 1, 1, 1);

        // Maximize button
        this->maximizeButton_ = new CustomButton(this->centralWidget_);
        this->maximizeButton_->setCustomName("dark-btn");
        QIcon maximizeButtonIcon;
        maximizeButtonIcon.addPixmap(QPixmap(":/rc/icons/maximize.png"), QIcon::Normal, QIcon::Off);
        this->maximizeButton_->setCustomIcon(maximizeButtonIcon, QSize(23, 23));
        connect(this->maximizeButton_, &QPushButton::clicked, this, [this]{ this->onMaximizeButtonClicked(); });
        this->topLayout_->addWidget(this->maximizeButton_, 0, 2, 1, 1);

        // Window widgets
        // this->menuBar = new QMenuBar();

        // Window tab widget
        this->tabWidget_ = new TabWidget();

        // Tabs
        QIcon welcomeIcon;
        welcomeIcon.addPixmap(QPixmap(":/rc/icons/voidstuff-logo.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget_->addTab(this->welcomeWidget_, QIcon(welcomeIcon), tr(""));
        this->tabWidget_->setIconSize(QSize(30, 30));

        QIcon sceneIcon;
        sceneIcon.addPixmap(QPixmap(":/rc/icons/scene-disabled.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget_->addTab(this->mainWidget_, QIcon(sceneIcon), tr(""));
        this->tabWidget_->setTabEnabled(1, false);
        this->tabWidget_->setIconSize(QSize(30, 30));

        QIcon codeEditorIcon;
        codeEditorIcon.addPixmap(QPixmap(":/rc/icons/code-editor-disabled.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget_->addTab(new QWidget(), QIcon(codeEditorIcon), tr(""));
        this->tabWidget_->setTabEnabled(2, false);
        this->tabWidget_->setIconSize(QSize(30, 30));

        QIcon settingsIcon;
        settingsIcon.addPixmap(QPixmap(":/rc/icons/settings.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget_->addTab(this->settingsWidget_, QIcon(settingsIcon), tr(""));
        this->tabWidget_->setIconSize(QSize(30, 30));

        QWidget* emptyWidget = new QWidget();
        this->tabWidget_->addTab(new QWidget(), "");
        this->tabWidget_->setTabEnabled(4, false);
        this->tabWidget_->tabBar()->setTabButton(4, QTabBar::LeftSide, emptyWidget);

        // Tools buttons
        QIcon runIcon;
        runIcon.addPixmap(QPixmap(":/rc/icons/run.png"), QIcon::Normal, QIcon::Off);
        this->runButton_ = new QToolButton();
        this->runButton_->setIcon(runIcon);
        this->runButton_->setEnabled(false);
        this->tabWidget_->addTab(new QWidget(), "");
        this->tabWidget_->setTabEnabled(5, false);
        this->tabWidget_->tabBar()->setTabButton(5, QTabBar::LeftSide, this->runButton_);

        QIcon buildIcon;
        buildIcon.addPixmap(QPixmap(":/rc/icons/build.png"), QIcon::Normal, QIcon::Off);
        this->buildButton_ = new QToolButton();
        this->buildButton_->setIcon(buildIcon);
        this->buildButton_->setEnabled(false);
        this->tabWidget_->addTab(new QWidget(), "");
        this->tabWidget_->setTabEnabled(6, false);
        this->tabWidget_->tabBar()->setTabButton(6, QTabBar::LeftSide, this->buildButton_);

        // Bind widgets and layout to window layout.
        this->windowLayout_ = new QVBoxLayout(this->centralWidget_);
        this->windowLayout_->setContentsMargins(0, 0, 0, 0);
        this->windowLayout_->addLayout(this->topLayout_);
        // this->windowLayout->addWidget(this->menuBar);
        this->windowLayout_->addWidget(this->tabWidget_);
        this->windowLayout_->addWidget(new QSizeGrip(this), 0, Qt::AlignBottom | Qt::AlignRight);

        // Bind central widget
        this->centralWidget_->setLayout(this->windowLayout_);
        this->setCentralWidget(this->centralWidget_);

        // Child connect components
        connect(this->welcomeWidget_->getCreateButton(), &QPushButton::clicked, this,
            &MainWindow::openProjectDialog);
    }

    /*
    void MainWindow::createMenus()
    {
        projectMenu = menuBar->addMenu(tr("Project"));
        projectMenu->addAction(openProjectDialogAction);

        editMenu = menuBar->addMenu(tr("Edit"));

        buildMenu = menuBar->addMenu(tr("Build"));

        settingsMenu = menuBar->addMenu(tr("Tools"));
        settingsMenu->addAction(openSettingDialogAction);
    }
    */

    /*
    void MainWindow::createActions()
    {
        openProjectDialogAction = new QAction(tr("New file or project"));
        openProjectDialogAction->setStatusTip(tr("Open file dialog"));
        connect(openProjectDialogAction, &QAction::triggered, this, &MainWindow::openProjectDialog);

        openSettingDialogAction = new QAction(tr("Settings"));
        openSettingDialogAction->setStatusTip(tr("Open settings dialog"));
        connect(openSettingDialogAction, &QAction::triggered, this, &MainWindow::openSettingsDialog);
    }
    */

    void MainWindow::mousePressEvent(QMouseEvent *event)
    {
        if(!this->windowTitleWidget_->underMouse())
            return;

        if(event->button() == Qt::LeftButton)
        {
            isMoving_ = true;
            this->lastMousePosition_ = event->pos();
        }
    }

    void MainWindow::mouseMoveEvent(QMouseEvent *event)
    {
        if(!this->windowTitleWidget_->underMouse())
            return;

        if(event->buttons().testFlag(Qt::LeftButton) && isMoving_)
            this->move(this->pos() + (event->pos() - this->lastMousePosition_));
    }

    void MainWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if(!this->windowTitleWidget_->underMouse())
            return;

        if(event->button() == Qt::LeftButton)
            isMoving_ = false;
    }

    void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
    {
        Q_UNUSED(event);

        if(!this->windowTitleWidget_->underMouse())
            return;

        onMaximizeButtonClicked();
    }

    void MainWindow::onExitButtonClicked()
    {
        this->close();
    }

    void MainWindow::onMaximizeButtonClicked()
    {
        if(this->isMaximized())
            this->showNormal();
        else
            this->showMaximized();
    }

    void MainWindow::onMinimizeButtonClicked()
    {
        this->showMinimized();
    }

    void MainWindow::openProjectDialog()
    {
        // this->projectDialog = new ProjectDialog();
        // this->projectDialog->show();

        // Reload (setup GLWidget) render window GUI.
        this->mainWidget_->getRenderWindow()->reloadUi();

        // Enable tabs.
        QIcon sceneIcon;
        sceneIcon.addPixmap(QPixmap(":/rc/icons/scene.png"), QIcon::Normal, QIcon::Off);

        QIcon codeEditorIcon;
        codeEditorIcon.addPixmap(QPixmap(":/rc/icons/code-editor.png"), QIcon::Normal, QIcon::Off);

        this->tabWidget_->setTabEnabled(1, true);
        this->tabWidget_->setTabIcon(1, sceneIcon);
        this->tabWidget_->setTabEnabled(2, true);
        this->tabWidget_->setTabIcon(2, codeEditorIcon);

        // Change current tab.
        this->tabWidget_->setCurrentIndex(1);

        // Enable run, build button
        this->runButton_->setEnabled(true);
        this->buildButton_->setEnabled(true);

        // delete projectDialog;
    }

    void MainWindow::openSettingsDialog()
    {
        // this->settingsDialog = new SettingsDialog();
        // this->settingsDialog->show();
    }

    void MainWindow::dockEngineWindow()
    {
        this->mainWidget_->dockGLWindow();
    }

    void MainWindow::undockEngineWindow()
    {
        if(this->mainWidget_->getRenderWindow() != nullptr)
            this->mainWidget_->undockGLWindow();
    }

    void MainWindow::addWindow(RenderWindow* _window)
    {
        if(_window == nullptr)
            return;

        // Init main widget.
        this->mainWidget_->setRenderWindow(_window);

        // Setup main window ui.
        init();
    }
}
