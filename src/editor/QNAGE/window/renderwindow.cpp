#include "renderwindow.h"
#include "widget/glwidget.h"
#include "widget/vkwidget.h"
#include "mainwindow.h"

namespace QNAGE
{
    RenderWindow::RenderWindow(MainWindow* _mainWindow)
        : FramelessWindow(_mainWindow, FRAMELESSWINDOW_WITHOUT_BUTTONS),
          mainWindow(_mainWindow),
          glWidget(nullptr),
          vkWidget(nullptr),
          isDocked(true),
          dockButton(nullptr)
    {
        setupUi();
    }

    RenderWindow::~RenderWindow()
    {
        delete vkWidget;
        delete glWidget;
        delete dockButton;
    }

    void RenderWindow::reloadUi()
    {
        // Add wigets to main layout.
        if(this->glWidget != nullptr)
        {
            // Dock engine window button
            this->dockButton = new CustomButton(this);
            this->dockButton->setObjectName("dark-btn");
            this->dockButton->setToolTip(tr("Dock / Undock engine window"));
            QIcon dockButtonIcon;
            dockButtonIcon.addPixmap(QPixmap(":/rc/icons/dock.png"), QIcon::Normal, QIcon::Off);
            this->dockButton->setCustomIcon(dockButtonIcon, QSize(15, 15));
            connect(this->dockButton, &QPushButton::clicked, this, [this]{ this->dockGLWindow(); });
            this->topLayout->addWidget(dockButton, 0, 3, 1, 1);

            // Add OpenGL widget to render window.
            this->layout->addWidget(glWidget);
        }
    }

    void RenderWindow::setupUi()
    {
        // Window initialize
        this->layout = new QVBoxLayout();
        this->setMainLayout(layout);

        // Add wigets to main layout.
        reloadUi();
    }

    void RenderWindow::setEngineWindowTitle(const QString &_title)
    {
        windowTitle = _title;
    }

    void RenderWindow::setupGLWidget(NAGE::IGame* _game)
    {
        if(glWidget == nullptr)
            glWidget = new GLWidget;

        glWidget->setGame(_game);
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
            isDocked = false;
            windowTitleWidget->setCursor(Qt::OpenHandCursor);

            // Show engine window.
            show();
        }
        else
        {
            if(!mainWindow->isEngineWindow())
            {
                if(mainWindow->isVisible())
                {
                    setAttribute(Qt::WA_DeleteOnClose, false);

                    // Window is pinned to main window.
                    isDocked = true;
                    windowTitleWidget->setCursor(Qt::ArrowCursor);

                    // Dock GLWindow to MainWindow
                    mainWindow->dockEngineWindow();
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
