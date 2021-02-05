#include "welcomewidget.h"

namespace mr::qnage
{
    WelcomeWidget::WelcomeWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        setupUi();
    }

    WelcomeWidget::~WelcomeWidget()
    {
        // TODO: clear widgets pointers.
    }

    void WelcomeWidget::setupUi()
    {
        // Main layout
        this->mainLayout_ = new QVBoxLayout();

        // App name
        this->appName_ = new QLabel();
        this->appName_->setText(tr("NAGE"));
        this->appName_->setFont(QFont("Arial", 18, QFont::Bold));

        // Buttons layout
        this->buttonsLayout_ = new QGridLayout();

        // Buttons
        this->createProjectButton_ = new QPushButton();
        this->createProjectButton_->setMinimumSize(QSize(155, 50));
        this->createProjectButton_->setMaximumSize(QSize(155, 50));
        this->createProjectButton_->setText(tr("New project"));
        QIcon addIcon;
        addIcon.addPixmap(QPixmap(":/rc/icons/plus.png"), QIcon::Normal, QIcon::Off);
        this->createProjectButton_->setIcon(addIcon);
        this->createProjectButton_->setIconSize(QSize(18, 18));
        this->createProjectButton_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

        this->openProjectButton_ = new QPushButton();
        this->openProjectButton_->setMinimumSize(QSize(155, 50));
        this->openProjectButton_->setMaximumSize(QSize(155, 50));
        this->openProjectButton_->setText(tr("Open project"));
        QIcon openIcon;
        openIcon.addPixmap(QPixmap(":/rc/icons/dir.png"), QIcon::Normal, QIcon::Off);
        this->openProjectButton_->setIcon(openIcon);
        this->openProjectButton_->setIconSize(QSize(18, 18));
        this->openProjectButton_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

        // Current session labels
        this->sessionLabel_ = new QLabel();
        this->sessionLabel_->setText(tr("Session"));
        this->sessionLabel_->setFont(QFont("Arial", 14, QFont::Bold));

        this->sessionDir_ = new QLabel();
        this->sessionDir_->setText(tr("~/"));
        this->sessionDir_->setFont(QFont("Arial", 11));

        // Layout spacers.
        this->horizontalSpacer_ = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->verticalSpacer1_ = new QSpacerItem(20, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->verticalSpacer2_ = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Add widgets to buttons layout.
        this->buttonsLayout_->addWidget(this->createProjectButton_, 0, 0);
        this->buttonsLayout_->addWidget(this->openProjectButton_, 0, 1);
        this->buttonsLayout_->addItem(this->horizontalSpacer_, 0, 2);

        // Add widgets to main layout.
        this->mainLayout_->addSpacerItem(this->verticalSpacer1_);
        this->mainLayout_->addWidget(this->appName_);
        this->mainLayout_->addLayout(this->buttonsLayout_);
        this->mainLayout_->addSpacerItem(this->verticalSpacer2_);
        this->mainLayout_->addWidget(this->sessionLabel_);
        this->mainLayout_->addWidget(this->sessionDir_);
        this->setLayout(this->mainLayout_);
    }
}
