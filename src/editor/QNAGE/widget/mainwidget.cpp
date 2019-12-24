#include "mainwidget.h"

namespace QNAGE
{
    MainWidget::MainWidget(QWidget* _parent)
        : QWidget(_parent)
    {

    }

    MainWidget::~MainWidget()
    {
        delete toolsWidget;
        delete logWidget;
        delete renderWindow;

        delete workspaceLayout;
        delete horizontalSplitter;
        delete workspaceWidget;

        delete verticalSplitter;
        delete mainLayout;
    }

    void MainWidget::setupUi()
    {
        // Main layout
        this->mainLayout = new QVBoxLayout();
        this->mainLayout->setContentsMargins(0, 0, 0, 0);

        // Workspace layout
        this->workspaceLayout = new QVBoxLayout();

        // Log output widget
        this->logWidget = new LogWidget();

        // Tools
        this->toolsWidget = new QWidget();

        // Splitter
        this->verticalSplitter = new QSplitter();
        this->horizontalSplitter = new QSplitter();

        // Bind widgets and layouts to main layout.
        this->workspaceWidget = new QWidget();
        this->horizontalSplitter->addWidget(this->renderWindow);
        this->horizontalSplitter->addWidget(this->toolsWidget);
        this->horizontalSplitter->setSizes(QList<int>({600, 150}));
        this->workspaceLayout->addWidget(this->horizontalSplitter);
        this->workspaceWidget->setLayout(this->workspaceLayout);

        this->verticalSplitter->setOrientation(Qt::Vertical);
        this->verticalSplitter->addWidget(this->workspaceWidget);
        this->verticalSplitter->addWidget(this->logWidget);
        this->verticalSplitter->setSizes(QList<int>({650, 150}));

        this->mainLayout->addWidget(this->verticalSplitter);
        this->setLayout(this->mainLayout);
    }

    void MainWidget::setRenderWindow(RenderWindow* _window)
    {
        if(_window == nullptr)
            return;

        renderWindow = _window;
        setupUi();
    }

    void MainWidget::dockGLWindow()
    {
        if(renderWindow == nullptr)
            return;

        this->horizontalSplitter->insertWidget(0, renderWindow);
    }

    void MainWidget::undockGLWindow()
    {
        if(renderWindow == nullptr)
            return;

        this->workspaceLayout->removeWidget(renderWindow);
    }
}
