#include "projectdialog.h"

namespace QNAGE
{
    ProjectDialog::ProjectDialog(QWidget* _parent)
        : FramelessWindow(_parent, FRAMELESSWINDOW_EXIT_BUTTON)
    {
        // Setup dialog window
        setupUi();
    }

    ProjectDialog::~ProjectDialog()
    {
        delete layout;
    }

    void ProjectDialog::setupUi()
    {
        // Main settings layout
        this->layout = new QVBoxLayout();
        this->layout->setContentsMargins(0, 0, 0, 0);

        // Init frameless window
        this->setMainLayout(layout);

        // Window settings
        this->setMinimumSize(800, 400);

        // Ui
        this->tabWidget = new TabWidget();

        // [PROJECT] Main layout
        this->createProjectLayout = new QVBoxLayout(this->tabWidget);

        this->projectMainLabel = new QLabel();
        this->projectMainLabel->setText(tr("Create a new project"));
        this->projectMainLabel->setFont(QFont("Arial", 18, QFont::Bold));
        this->createProjectLayout->addWidget(this->projectMainLabel, 0, Qt::AlignTop);

        this->projectMainDescription = new QLabel();
        this->projectMainDescription->setText(tr("This wizard generates a new game project."));
        this->projectMainDescription->setFont(QFont("Arial", 10));
        this->createProjectLayout->addWidget(this->projectMainDescription, 0, Qt::AlignTop);

        this->createProjectLayout->addStretch(1);

        // [PROJECT] Main widgets layout
        this->projectWidgetsLayout = new QGridLayout();
        this->projectWidgetsLayout->setVerticalSpacing(10);

        this->projectNameInput = new QLineEdit();
        this->projectWidgetsLayout->addWidget(new QLabel(tr("Project name:")), 0, 0);
        this->projectWidgetsLayout->addWidget(this->projectNameInput, 0, 1);

        this->projectDirInput = new QLineEdit();
        this->projectWidgetsLayout->addWidget(new QLabel(tr("Create in:")), 1, 0);
        this->projectWidgetsLayout->addWidget(this->projectDirInput, 1, 1);

        this->createProjectWidget = new QWidget();
        this->createProjectLayout->addLayout(this->projectWidgetsLayout);
        this->createProjectWidget->setLayout(this->createProjectLayout);

        this->browseButton = new QPushButton();
        this->browseButton->setText(tr("Browse"));
        this->projectWidgetsLayout->addWidget(this->browseButton, 1, 2);

        // [PROJECT] Create project buttons
        this->createButton = new QPushButton();
        this->createButton->setText(tr("Create project"));
        this->projectWidgetsLayout->addWidget(this->createButton, 3, 2);

        this->cancelButton = new QPushButton();
        this->cancelButton->setText(tr("Cancel"));
        this->projectWidgetsLayout->addWidget(this->cancelButton, 3, 3);

        // [FILE] Create a new file (cpp)

        QIcon projectIcon;
        projectIcon.addPixmap(QPixmap(":/rc/icons/project.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget->addTab(this->createProjectWidget, QIcon(projectIcon), tr(""));
        this->tabWidget->setIconSize(QSize(40, 40));

        QIcon cPlusPlusIcon;
        cPlusPlusIcon.addPixmap(QPixmap(":/rc/icons/cplusplus.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget->addTab(new QWidget(), QIcon(cPlusPlusIcon), tr(""));
        this->tabWidget->setIconSize(QSize(40, 40));

        this->layout->addWidget(tabWidget);
        this->layout->addWidget(new QSizeGrip(this), 0, Qt::AlignBottom | Qt::AlignRight);
    }
}
