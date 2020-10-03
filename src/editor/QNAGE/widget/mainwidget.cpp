#include "mainwidget.h"

namespace mr::qnage
{
    MainWidget::MainWidget(QWidget* _parent)
        : QWidget(_parent)
    {

    }

    MainWidget::~MainWidget()
    {
        delete toolsWidget_;
        delete logWidget_;
        delete renderWindow_;

        delete workspaceLayout_;
        delete horizontalSplitter_;
        delete workspaceWidget_;

        delete verticalSplitter_;
        delete mainLayout_;
    }

    void MainWidget::setupUi()
    {
        // Main layout
        this->mainLayout_ = new QVBoxLayout();
        this->mainLayout_->setContentsMargins(0, 0, 0, 0);

        // Workspace layout
        this->workspaceLayout_ = new QVBoxLayout();

        // Log output widget
        this->logWidget_ = new LogWidget();

        // Tools
        this->toolsWidget_ = new QWidget();

        // Splitter
        this->verticalSplitter_ = new QSplitter();
        this->horizontalSplitter_ = new QSplitter();

        // Bind widgets and layouts to main layout.
        this->workspaceWidget_ = new QWidget();
        this->horizontalSplitter_->addWidget(this->renderWindow_);
        this->horizontalSplitter_->addWidget(this->toolsWidget_);
        this->horizontalSplitter_->setSizes(QList<int>({600, 150}));
        this->workspaceLayout_->addWidget(this->horizontalSplitter_);
        this->workspaceWidget_->setLayout(this->workspaceLayout_);

        this->verticalSplitter_->setOrientation(Qt::Vertical);
        this->verticalSplitter_->addWidget(this->workspaceWidget_);
        this->verticalSplitter_->addWidget(this->logWidget_);
        this->verticalSplitter_->setSizes(QList<int>({650, 150}));

        this->mainLayout_->addWidget(this->verticalSplitter_);
        this->setLayout(this->mainLayout_);
    }

    void MainWidget::setRenderWindow(RenderWindow* _window)
    {
        if(_window == nullptr)
            return;

        renderWindow_ = _window;
        setupUi();
    }

    void MainWidget::dockGLWindow()
    {
        if(renderWindow_ == nullptr)
            return;

        this->horizontalSplitter_->insertWidget(0, renderWindow_);
    }

    void MainWidget::undockGLWindow()
    {
        if(renderWindow_ == nullptr)
            return;

        this->workspaceLayout_->removeWidget(renderWindow_);
    }
}
