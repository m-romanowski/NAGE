#include "framelesswindow.h"

namespace QNAGE
{
    FramelessWindow::FramelessWindow(QWidget* _parent, unsigned int _type)
        : QWidget(_parent),
          type_(_type),
          exitButton_(nullptr),
          minimizeButton_(nullptr),
          maximizeButton_(nullptr)
    {
        this->setObjectName("app-window");
    }

    FramelessWindow::~FramelessWindow()
    {
        delete exitButton_;
        delete minimizeButton_;
        delete maximizeButton_;

        delete windowTitleWidget_;
        delete topLayout_;
        delete topLayoutWidget_;
        delete mainLayout_;
    }

    void FramelessWindow::init()
    {
        // Window settings
        this->setMouseTracking(true);
        this->setWindowFlags(Qt::FramelessWindowHint);

        // Top layout
        this->topLayout_ = new QGridLayout();
        this->topLayout_->setContentsMargins(6, 6, 6, 6);
        this->topLayout_->setAlignment(Qt::AlignTop);

        this->windowTitleWidget_ = new QWidget(this);
        this->windowTitleWidget_->setCursor(Qt::OpenHandCursor);
        this->topLayout_->addWidget(this->windowTitleWidget_, 0, 0, 1, 1);

        if(type_ != 0)
        {
            // Exit button
            this->exitButton_ = new CustomButton(this);
            this->exitButton_->setCustomName("exit-btn");
            QIcon exitButtonIcon;
            exitButtonIcon.addPixmap(QPixmap(":/rc/icons/close.png"), QIcon::Normal, QIcon::Off);
            this->exitButton_->setCustomIcon(exitButtonIcon, QSize(23, 23));
            connect(this->exitButton_, &QPushButton::clicked, this, [this]{ this->onExitButtonClicked(); });
            this->topLayout_->addWidget(this->exitButton_, 0, 3, 1, 1);

            // Minimize button
            if(type_ == 1 || type_ == 3)
            {
                this->minimizeButton_ = new CustomButton(this);
                this->minimizeButton_->setCustomName("minimize-btn");
                QIcon minimizeButtonIcon;
                minimizeButtonIcon.addPixmap(QPixmap(":/rc/icons/minimize.png"), QIcon::Normal, QIcon::Off);
                this->minimizeButton_->setCustomIcon(minimizeButtonIcon, QSize(23, 23));
                connect(this->minimizeButton_, &QPushButton::clicked, this, [this]{ this->onMinimizeButtonClicked(); });
                this->topLayout_->addWidget(this->minimizeButton_, 0, 1, 1, 1);
            }

            // Maximize button
            if(type_ == 1)
            {
                this->maximizeButton_ = new CustomButton(this);
                this->maximizeButton_->setCustomName("maximize-btn");
                QIcon maximizeButtonIcon;
                maximizeButtonIcon.addPixmap(QPixmap(":/rc/icons/maximize.png"), QIcon::Normal, QIcon::Off);
                this->maximizeButton_->setCustomIcon(maximizeButtonIcon, QSize(23, 23));
                connect(this->maximizeButton_, &QPushButton::clicked, this, [this]{ this->onMaximizeButtonClicked(); });
                this->topLayout_->addWidget(this->maximizeButton_, 0, 2, 1, 1);
            }
        }

        // Add widgets to main layout.
        this->topLayoutWidget_ = new QWidget();
        this->topLayoutWidget_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        this->topLayoutWidget_->setLayout(topLayout_);
        this->mainLayout_->addWidget(topLayoutWidget_);

        // Bind central widget
        this->setLayout(mainLayout_);
    }

    void FramelessWindow::mousePressEvent(QMouseEvent* _event)
    {
        if(!this->windowTitleWidget_->underMouse())
            return;

        if(_event->button() == Qt::LeftButton)
        {
            isMoving_ = true;
            this->lastMousePosition_ = _event->pos();
        }
    }

    void FramelessWindow::mouseMoveEvent(QMouseEvent* _event)
    {
        if(!this->windowTitleWidget_->underMouse())
            return;

        if(_event->buttons().testFlag(Qt::LeftButton) && isMoving_)
            this->move(this->pos() + (_event->pos() - this->lastMousePosition_));
    }

    void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if(!this->windowTitleWidget_->underMouse())
            return;

        if(event->button() == Qt::LeftButton)
            isMoving_ = false;
    }

    void FramelessWindow::mouseDoubleClickEvent(QMouseEvent* _event)
    {
        Q_UNUSED(_event);

        if(!this->windowTitleWidget_->underMouse())
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
