#include "renderwindow.h"
#include "widget/glwidget.h"
#include "widget/vkwidget.h"
#include "mainwindow.h"

// TODO: move to the bridge qt <-> x11
#include "engine/io/x11openglwindow.h"

namespace mr::qnage
{
    RenderWindow::RenderWindow(MainWindow* _mainWindow)
        : FramelessWindow(_mainWindow, FRAMELESSWINDOW_WITHOUT_BUTTONS),
          mainWindow_(_mainWindow),
          glWidget_(nullptr),
          vkWidget_(nullptr),
          isDocked_(true),
          dockButton_(nullptr)
    {
        setupUi();
    }

    RenderWindow::~RenderWindow()
    {
        delete vkWidget_;
        delete glWidget_;
        delete dockButton_;
    }

    void RenderWindow::reloadUi()
    {
        // Add wigets to main layout.
        if(this->glWidget_ != nullptr)
        {
            // Dock engine window button
            this->dockButton_ = new CustomButton(this);
            this->dockButton_->setObjectName("dark-btn");
            this->dockButton_->setToolTip(tr("Dock / Undock engine window"));
            QIcon dockButtonIcon;
            dockButtonIcon.addPixmap(QPixmap(":/rc/icons/dock.png"), QIcon::Normal, QIcon::Off);
            this->dockButton_->setCustomIcon(dockButtonIcon, QSize(15, 15));
            connect(this->dockButton_, &QPushButton::clicked, this, [this]{ this->dockGLWindow(); });
            this->topLayout_->addWidget(dockButton_, 0, 3, 1, 1);

            // Add OpenGL widget to render window.
            this->glWidget_->startRendering();
            this->layout_->addWidget(glWidget_);
        }
    }

    void RenderWindow::setupUi()
    {
        // Window initialize
        this->layout_ = new QVBoxLayout();
        this->setMainLayout(layout_);

        // Add wigets to main layout.
        reloadUi();
    }

    void RenderWindow::setEngineWindowTitle(const QString &_title)
    {
        windowTitle_ = _title;
    }

    void RenderWindow::setupGLWidget(nage::IGame* _game)
    {
        if(glWidget_ == nullptr)
            glWidget_ = new GLWidget;

        glWidget_->initialize(_game);
        connect(glWidget_, &GLWidget::ready, this, [this]() {
            this->mainWindow_->mainWidget()->sceneWidget()->sceneTree()->setSceneHandler(glWidget_->game()->sceneManager());
        }, Qt::ConnectionType::QueuedConnection);
    }

    void RenderWindow::dockGLWindow()
    {
        if(parent())
        {
            setParent(nullptr);
            setAttribute(Qt::WA_DeleteOnClose);
            move(QApplication::desktop()->width() / 2 - width() / 2,
                 QApplication::desktop()->height() / 2 - height() / 2);

            // Window is not pinned to main window.
            isDocked_ = false;
            windowTitleWidget_->setCursor(Qt::OpenHandCursor);

            // Show engine window.
            show();
        }
        else
        {
            if(!mainWindow_->isEngineWindow())
            {
                if(mainWindow_->isVisible())
                {
                    setAttribute(Qt::WA_DeleteOnClose, false);

                    // Window is pinned to main window.
                    isDocked_ = true;
                    windowTitleWidget_->setCursor(Qt::ArrowCursor);

                    // Dock GLWindow to MainWindow
                    mainWindow_->dockEngineWindow();
                }
                else
                {
                    QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already closed"));
                }
            }
            else
            {
                QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already occupied"));
            }
        }
    }
}
