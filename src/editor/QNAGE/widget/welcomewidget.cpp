#include "welcomewidget.h"

namespace QNAGE
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
        this->mainLayout = new QVBoxLayout();

        // App name
        this->appName = new QLabel();
        this->appName->setText(tr("NAGE"));
        this->appName->setFont(QFont("Arial", 18, QFont::Bold));

        // Buttons layout
        this->buttonsLayout = new QGridLayout();

        // Buttons
        this->createProjectButton = new QPushButton();
        this->createProjectButton->setMinimumSize(QSize(155, 50));
        this->createProjectButton->setMaximumSize(QSize(155, 50));
        this->createProjectButton->setText(tr("New project"));
        QIcon addIcon;
        addIcon.addPixmap(QPixmap(":/rc/icons/plus.png"), QIcon::Normal, QIcon::Off);
        this->createProjectButton->setIcon(addIcon);
        this->createProjectButton->setIconSize(QSize(18, 18));
        this->createProjectButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

        this->openProjectButton = new QPushButton();
        this->openProjectButton->setMinimumSize(QSize(155, 50));
        this->openProjectButton->setMaximumSize(QSize(155, 50));
        this->openProjectButton->setText(tr("Open project"));
        QIcon openIcon;
        openIcon.addPixmap(QPixmap(":/rc/icons/dir.png"), QIcon::Normal, QIcon::Off);
        this->openProjectButton->setIcon(openIcon);
        this->openProjectButton->setIconSize(QSize(18, 18));
        this->openProjectButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

        // Current session labels
        this->sessionLabel = new QLabel();
        this->sessionLabel->setText(tr("Session"));
        this->sessionLabel->setFont(QFont("Arial", 14, QFont::Bold));

        this->sessionDir = new QLabel();
        this->sessionDir->setText(tr("~/home/projects/OpenGL/hypercube"));
        this->sessionDir->setFont(QFont("Arial", 11));

        // Layout spacers.
        this->horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->verticalSpacer1 = new QSpacerItem(20, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->verticalSpacer2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Add widgets to buttons layout.
        this->buttonsLayout->addWidget(this->createProjectButton, 0, 0);
        this->buttonsLayout->addWidget(this->openProjectButton, 0, 1);
        this->buttonsLayout->addItem(this->horizontalSpacer, 0, 2);

        // Add widgets to main layout.
        this->mainLayout->addSpacerItem(this->verticalSpacer1);
        this->mainLayout->addWidget(this->appName);
        this->mainLayout->addLayout(this->buttonsLayout);
        this->mainLayout->addSpacerItem(this->verticalSpacer2);
        this->mainLayout->addWidget(this->sessionLabel);
        this->mainLayout->addWidget(this->sessionDir);
        this->setLayout(this->mainLayout);
    }
}
