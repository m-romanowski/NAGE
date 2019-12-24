#include "mainwindow.h"

namespace QNAGE
{
    MainWindow::MainWindow(int _width, int _height)
        : width(_width),
          height(_height),
          isMoving(false),
          lastMousePosition(QPoint(0, 0)),
          mainWidget(new MainWidget),
          welcomeWidget(new WelcomeWidget),
          settingsWidget(new SettingsWidget)
    {
        this->setMinimumSize(width, height);
    }

    MainWindow::~MainWindow()
    {
        // Menus, Actions
        delete openProjectDialogAction;
        delete openSettingDialogAction;
        // delete settingsMenu;
        // delete buildMenu;
        // delete editMenu;
        // delete projectMenu;
        // delete menuBar;

        // Buttons
        delete buildButton;
        delete runButton;
        delete exitButton;
        delete minimizeButton;
        delete maximizeButton;

        // Widgets
        delete windowTitleWidget;
        delete settingsWidget;
        delete welcomeWidget;
        delete mainWidget;

        // Layouts, main window widgets.
        delete tabWidget;
        delete topLayout;
        delete windowLayout;
        delete centralWidget;
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
        this->centralWidget = new QWidget(this);

        // Top layout
        this->topLayout = new QGridLayout();
        this->topLayout->setContentsMargins(6, 6, 6, 6);

        this->windowTitleWidget = new QWidget(this->centralWidget);
        this->windowTitleWidget->setCursor(Qt::OpenHandCursor);
        this->topLayout->addWidget(this->windowTitleWidget, 0, 0, 1, 1);

        // Exit button
        this->exitButton = new CustomButton(this->centralWidget);
        this->exitButton->setCustomName("exit-btn");
        QIcon exitButtonIcon;
        exitButtonIcon.addPixmap(QPixmap(":/rc/icons/close.png"), QIcon::Normal, QIcon::Off);
        this->exitButton->setCustomIcon(exitButtonIcon, QSize(23, 23));
        connect(this->exitButton, &QPushButton::clicked, this, [this]{ this->onExitButtonClicked(); });
        this->topLayout->addWidget(this->exitButton, 0, 3, 1, 1);

        // Minimize button
        this->minimizeButton = new CustomButton(this->centralWidget);
        this->minimizeButton->setCustomName("dark-btn");
        QIcon minimizeButtonIcon;
        minimizeButtonIcon.addPixmap(QPixmap(":/rc/icons/minimize.png"), QIcon::Normal, QIcon::Off);
        this->minimizeButton->setCustomIcon(minimizeButtonIcon, QSize(23, 23));
        connect(this->minimizeButton, &QPushButton::clicked, this, [this]{ this->onMinimizeButtonClicked(); });
        this->topLayout->addWidget(this->minimizeButton, 0, 1, 1, 1);

        // Maximize button
        this->maximizeButton = new CustomButton(this->centralWidget);
        this->maximizeButton->setCustomName("dark-btn");
        QIcon maximizeButtonIcon;
        maximizeButtonIcon.addPixmap(QPixmap(":/rc/icons/maximize.png"), QIcon::Normal, QIcon::Off);
        this->maximizeButton->setCustomIcon(maximizeButtonIcon, QSize(23, 23));
        connect(this->maximizeButton, &QPushButton::clicked, this, [this]{ this->onMaximizeButtonClicked(); });
        this->topLayout->addWidget(this->maximizeButton, 0, 2, 1, 1);

        // Window widgets
        // this->menuBar = new QMenuBar();

        // Window tab widget
        this->tabWidget = new TabWidget();

        // Tabs
        QIcon welcomeIcon;
        welcomeIcon.addPixmap(QPixmap(":/rc/icons/voidstuff-logo.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget->addTab(this->welcomeWidget, QIcon(welcomeIcon), tr(""));
        this->tabWidget->setIconSize(QSize(30, 30));

        QIcon sceneIcon;
        sceneIcon.addPixmap(QPixmap(":/rc/icons/scene-disabled.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget->addTab(this->mainWidget, QIcon(sceneIcon), tr(""));
        this->tabWidget->setTabEnabled(1, false);
        this->tabWidget->setIconSize(QSize(30, 30));

        QIcon codeEditorIcon;
        codeEditorIcon.addPixmap(QPixmap(":/rc/icons/code-editor-disabled.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget->addTab(new QWidget(), QIcon(codeEditorIcon), tr(""));
        this->tabWidget->setTabEnabled(2, false);
        this->tabWidget->setIconSize(QSize(30, 30));

        QIcon settingsIcon;
        settingsIcon.addPixmap(QPixmap(":/rc/icons/settings.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget->addTab(this->settingsWidget, QIcon(settingsIcon), tr(""));
        this->tabWidget->setIconSize(QSize(30, 30));

        QWidget* emptyWidget = new QWidget();
        this->tabWidget->addTab(new QWidget(), "");
        this->tabWidget->setTabEnabled(4, false);
        this->tabWidget->tabBar()->setTabButton(4, QTabBar::LeftSide, emptyWidget);

        // Tools buttons
        QIcon runIcon;
        runIcon.addPixmap(QPixmap(":/rc/icons/run.png"), QIcon::Normal, QIcon::Off);
        this->runButton = new QToolButton();
        this->runButton->setIcon(runIcon);
        this->runButton->setEnabled(false);
        this->tabWidget->addTab(new QWidget(), "");
        this->tabWidget->setTabEnabled(5, false);
        this->tabWidget->tabBar()->setTabButton(5, QTabBar::LeftSide, this->runButton);

        QIcon buildIcon;
        buildIcon.addPixmap(QPixmap(":/rc/icons/build.png"), QIcon::Normal, QIcon::Off);
        this->buildButton = new QToolButton();
        this->buildButton->setIcon(buildIcon);
        this->buildButton->setEnabled(false);
        this->tabWidget->addTab(new QWidget(), "");
        this->tabWidget->setTabEnabled(6, false);
        this->tabWidget->tabBar()->setTabButton(6, QTabBar::LeftSide, this->buildButton);

        // Bind widgets and layout to window layout.
        this->windowLayout = new QVBoxLayout(this->centralWidget);
        this->windowLayout->setContentsMargins(0, 0, 0, 0);
        this->windowLayout->addLayout(this->topLayout);
        // this->windowLayout->addWidget(this->menuBar);
        this->windowLayout->addWidget(this->tabWidget);
        this->windowLayout->addWidget(new QSizeGrip(this), 0, Qt::AlignBottom | Qt::AlignRight);

        // Bind central widget
        this->centralWidget->setLayout(this->windowLayout);
        this->setCentralWidget(this->centralWidget);

        // Child connect components
        connect(this->welcomeWidget->getCreateButton(), &QPushButton::clicked, this,
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
        if(!this->windowTitleWidget->underMouse())
            return;

        if(event->button() == Qt::LeftButton)
        {
            isMoving = true;
            this->lastMousePosition = event->pos();
        }
    }

    void MainWindow::mouseMoveEvent(QMouseEvent *event)
    {
        if(!this->windowTitleWidget->underMouse())
            return;

        if(event->buttons().testFlag(Qt::LeftButton) && isMoving)
            this->move(this->pos() + (event->pos() - this->lastMousePosition));
    }

    void MainWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if(!this->windowTitleWidget->underMouse())
            return;

        if(event->button() == Qt::LeftButton)
            isMoving = false;
    }

    void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
    {
        Q_UNUSED(event);

        if(!this->windowTitleWidget->underMouse())
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
        this->mainWidget->getRenderWindow()->reloadUi();

        // Enable tabs.
        QIcon sceneIcon;
        sceneIcon.addPixmap(QPixmap(":/rc/icons/scene.png"), QIcon::Normal, QIcon::Off);

        QIcon codeEditorIcon;
        codeEditorIcon.addPixmap(QPixmap(":/rc/icons/code-editor.png"), QIcon::Normal, QIcon::Off);

        this->tabWidget->setTabEnabled(1, true);
        this->tabWidget->setTabIcon(1, sceneIcon);
        this->tabWidget->setTabEnabled(2, true);
        this->tabWidget->setTabIcon(2, codeEditorIcon);

        // Change current tab.
        this->tabWidget->setCurrentIndex(1);

        // Enable run, build button
        this->runButton->setEnabled(true);
        this->buildButton->setEnabled(true);

        // delete projectDialog;
    }

    void MainWindow::openSettingsDialog()
    {
        // this->settingsDialog = new SettingsDialog();
        // this->settingsDialog->show();
    }

    void MainWindow::dockEngineWindow()
    {
        this->mainWidget->dockGLWindow();
    }

    void MainWindow::undockEngineWindow()
    {
        if(this->mainWidget->getRenderWindow() != nullptr)
            this->mainWidget->undockGLWindow();
    }

    void MainWindow::addWindow(RenderWindow* _window)
    {
        if(_window == nullptr)
            return;

        // Init main widget.
        this->mainWidget->setRenderWindow(_window);

        // Setup main window ui.
        init();
    }
}
