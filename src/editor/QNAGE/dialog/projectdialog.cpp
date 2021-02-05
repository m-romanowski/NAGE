#include "projectdialog.h"

namespace mr::qnage
{
    ProjectDialog::ProjectDialog(QWidget* _parent)
        : Dialog(_parent)
    {
        // Setup dialog window
        setupUi();
    }

    ProjectDialog::~ProjectDialog()
    {
        delete layout_;
    }

    void ProjectDialog::setupUi()
    {
        // Main settings layout_
        this->layout_ = new QVBoxLayout();
        this->layout_->setContentsMargins(0, 0, 0, 0);

        // Init frameless window
        this->setMainLayout(layout_);

        // Window settings
        this->setMinimumSize(800, 400);

        // Ui
        this->tabWidget_ = new TabWidget();

        // [PROJECT] Main layout_
        this->createProjectLayout_ = new QVBoxLayout(this->tabWidget_);

        this->projectMainLabel_ = new QLabel();
        this->projectMainLabel_->setText(tr("Create a new project"));
        this->projectMainLabel_->setFont(QFont("Arial", 18, QFont::Bold));
        this->createProjectLayout_->addWidget(this->projectMainLabel_, 0, Qt::AlignTop);

        this->projectMainDescription_ = new QLabel();
        this->projectMainDescription_->setText(tr("This wizard generates a new game project."));
        this->projectMainDescription_->setFont(QFont("Arial", 10));
        this->createProjectLayout_->addWidget(this->projectMainDescription_, 0, Qt::AlignTop);

        this->createProjectLayout_->addStretch(1);

        // [PROJECT] Main widgets layout_
        this->projectWidgetsLayout_ = new QGridLayout();
        this->projectWidgetsLayout_->setVerticalSpacing(10);

        this->projectNameInput_ = new QLineEdit();
        this->projectWidgetsLayout_->addWidget(new QLabel(tr("Project name:")), 0, 0);
        this->projectWidgetsLayout_->addWidget(this->projectNameInput_, 0, 1);

        this->projectDirInput_ = new QLineEdit();
        this->projectWidgetsLayout_->addWidget(new QLabel(tr("Create in:")), 1, 0);
        this->projectWidgetsLayout_->addWidget(this->projectDirInput_, 1, 1);

        this->createProjectWidget_ = new QWidget();
        this->createProjectLayout_->addLayout(this->projectWidgetsLayout_);
        this->createProjectWidget_->setLayout(this->createProjectLayout_);

        this->browseButton_ = new QPushButton();
        this->browseButton_->setText(tr("Browse"));
        this->projectWidgetsLayout_->addWidget(this->browseButton_, 1, 2);

        // [PROJECT] Create project buttons
        this->createButton_ = new QPushButton();
        this->createButton_->setText(tr("Create project"));
        this->projectWidgetsLayout_->addWidget(this->createButton_, 3, 2);

        this->cancelButton_ = new QPushButton();
        this->cancelButton_->setText(tr("Cancel"));
        this->projectWidgetsLayout_->addWidget(this->cancelButton_, 3, 3);

        // [FILE] Create a new file (cpp)
        QIcon projectIcon;
        projectIcon.addPixmap(QPixmap(":/rc/icons/project.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget_->addTab(this->createProjectWidget_, QIcon(projectIcon), tr(""));
        this->tabWidget_->setIconSize(QSize(40, 40));

        QIcon cPlusPlusIcon;
        cPlusPlusIcon.addPixmap(QPixmap(":/rc/icons/cplusplus.png"), QIcon::Normal, QIcon::Off);
        this->tabWidget_->addTab(new QWidget(), QIcon(cPlusPlusIcon), tr(""));
        this->tabWidget_->setIconSize(QSize(40, 40));

        this->layout_->addWidget(this->tabWidget_);
        this->layout_->addWidget(new QSizeGrip(this), 0, Qt::AlignBottom | Qt::AlignRight);
    }
}
