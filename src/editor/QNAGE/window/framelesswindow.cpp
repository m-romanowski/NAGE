#include "framelesswindow.h"

namespace QNAGE
{
    FramelessWindow::FramelessWindow(QWidget* _parent, unsigned int _type)
        : QWidget(_parent),
          type(_type),
          exitButton(nullptr),
          minimizeButton(nullptr),
          maximizeButton(nullptr)
    {
        this->setObjectName("app-window");
    }

    FramelessWindow::~FramelessWindow()
    {
        delete exitButton;
        delete minimizeButton;
        delete maximizeButton;

        delete windowTitleWidget;
        delete topLayout;
        delete topLayoutWidget;
        delete mainLayout;
    }

    void FramelessWindow::init()
    {
        // Window settings
        this->setMouseTracking(true);
        this->setWindowFlags(Qt::FramelessWindowHint);

        // Top layout
        this->topLayout = new QGridLayout();
        this->topLayout->setContentsMargins(6, 6, 6, 6);
        this->topLayout->setAlignment(Qt::AlignTop);

        this->windowTitleWidget = new QWidget(this);
        this->windowTitleWidget->setCursor(Qt::OpenHandCursor);
        this->topLayout->addWidget(this->windowTitleWidget, 0, 0, 1, 1);

        if(type != 0)
        {
            // Exit button
            this->exitButton = new CustomButton(this);
            this->exitButton->setCustomName("exit-btn");
            QIcon exitButtonIcon;
            exitButtonIcon.addPixmap(QPixmap(":/rc/icons/close.png"), QIcon::Normal, QIcon::Off);
            this->exitButton->setCustomIcon(exitButtonIcon, QSize(23, 23));
            connect(this->exitButton, &QPushButton::clicked, this, [this]{ this->onExitButtonClicked(); });
            this->topLayout->addWidget(this->exitButton, 0, 3, 1, 1);

            // Minimize button
            if(type == 1 || type == 3)
            {
                this->minimizeButton = new CustomButton(this);
                this->minimizeButton->setCustomName("minimize-btn");
                QIcon minimizeButtonIcon;
                minimizeButtonIcon.addPixmap(QPixmap(":/rc/icons/minimize.png"), QIcon::Normal, QIcon::Off);
                this->minimizeButton->setCustomIcon(minimizeButtonIcon, QSize(23, 23));
                connect(this->minimizeButton, &QPushButton::clicked, this, [this]{ this->onMinimizeButtonClicked(); });
                this->topLayout->addWidget(this->minimizeButton, 0, 1, 1, 1);
            }

            // Maximize button
            if(type == 1)
            {
                this->maximizeButton = new CustomButton(this);
                this->maximizeButton->setCustomName("maximize-btn");
                QIcon maximizeButtonIcon;
                maximizeButtonIcon.addPixmap(QPixmap(":/rc/icons/maximize.png"), QIcon::Normal, QIcon::Off);
                this->maximizeButton->setCustomIcon(maximizeButtonIcon, QSize(23, 23));
                connect(this->maximizeButton, &QPushButton::clicked, this, [this]{ this->onMaximizeButtonClicked(); });
                this->topLayout->addWidget(this->maximizeButton, 0, 2, 1, 1);
            }
        }

        // Add widgets to main layout.
        this->topLayoutWidget = new QWidget();
        this->topLayoutWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        this->topLayoutWidget->setLayout(topLayout);
        this->mainLayout->addWidget(topLayoutWidget);

        // Bind central widget
        this->setLayout(mainLayout);
    }

    void FramelessWindow::mousePressEvent(QMouseEvent* _event)
    {
        if(!this->windowTitleWidget->underMouse())
            return;

        if(_event->button() == Qt::LeftButton)
        {
            isMoving = true;
            this->lastMousePosition = _event->pos();
        }
    }

    void FramelessWindow::mouseMoveEvent(QMouseEvent* _event)
    {
        if(!this->windowTitleWidget->underMouse())
            return;

        if(_event->buttons().testFlag(Qt::LeftButton) && isMoving)
            this->move(this->pos() + (_event->pos() - this->lastMousePosition));
    }

    void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if(!this->windowTitleWidget->underMouse())
            return;

        if(event->button() == Qt::LeftButton)
            isMoving = false;
    }

    void FramelessWindow::mouseDoubleClickEvent(QMouseEvent* _event)
    {
        Q_UNUSED(_event);

        if(!this->windowTitleWidget->underMouse())
            return;

        onMaximizeButtonClicked();
    }

    void FramelessWindow::onExitButtonClicked()
    {
        this->close();
    }

    void FramelessWindow::onMaximizeButtonClicked()
    {
        if(this->isMaximized())
            this->showNormal();
        else
            this->showMaximized();
    }

    void FramelessWindow::onMinimizeButtonClicked()
    {
        this->showMinimized();
    }
}
