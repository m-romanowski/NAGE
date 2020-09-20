#include "settingsnavigation.h"

namespace QNAGE
{
    SettingsNavigation::SettingsNavigation(QWidget* _parent)
        : SettingsLayout(_parent)
    {
        setupUi();
    }

    SettingsNavigation::~SettingsNavigation()
    {
        delete environmentButton_;
        delete engineButton_;
        delete buildAndRunButton_;
        delete navigationLayout_;
        delete environmentSettings_;
        delete engineSettings_;
        delete buildAndRunSettings_;
    }

    void SettingsNavigation::setupUi()
    {
        // Create settings widgets.
        this->environmentSettings_ = new EnvironmentSettings();
        this->engineSettings_ = new EngineSettings();
        this->buildAndRunSettings_ = new BuildAndRunSettings();

        // Bind widgets
        bindNavigationWidgets();
    }

    void SettingsNavigation::bindNavigationWidgets()
    {
        connect(this->backButton_, &QPushButton::clicked, this, &SettingsNavigation::bindNavigationWidgets);

        this->navigationWidget_ = new QWidget();

        // Navigation layout.
        this->navigationLayout_ = new QGridLayout();

        this->environmentButton_ = new QToolButton();
        this->environmentButton_->setText(QString("Environment"));
        this->environmentButton_->setFixedSize(QSize(185, 185));
        this->environmentButton_->setStyleSheet("padding: 15px;");
        QIcon environmentIcon;
        environmentIcon.addPixmap(QPixmap(":/rc/icons/environment.png"), QIcon::Normal, QIcon::Off);
        this->environmentButton_->setIcon(environmentIcon);
        this->environmentButton_->setIconSize(QSize(100, 100));
        this->environmentButton_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(this->environmentButton_, &QToolButton::clicked, this, &SettingsNavigation::bindEnvironmentWidgets);

        this->engineButton_ = new QToolButton();
        this->engineButton_->setText(QString("Engine"));
        this->engineButton_->setFixedSize(QSize(185, 185));
        this->engineButton_->setStyleSheet("padding: 15px;");
        QIcon engineIcon;
        engineIcon.addPixmap(QPixmap(":/rc/icons/welcome.png"), QIcon::Normal, QIcon::Off);
        this->engineButton_->setIcon(engineIcon);
        this->engineButton_->setIconSize(QSize(100, 100));
        this->engineButton_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(this->engineButton_, &QToolButton::clicked, this, &SettingsNavigation::bindEngineWidgets);

        this->buildAndRunButton_ = new QToolButton();
        this->buildAndRunButton_->setText(QString("Build && Run"));
        this->buildAndRunButton_->setFixedSize(QSize(185, 185));
        this->buildAndRunButton_->setStyleSheet("padding: 15px;");
        QIcon buildAndRunIcon;
        buildAndRunIcon.addPixmap(QPixmap(":/rc/icons/build.png"), QIcon::Normal, QIcon::Off);
        this->buildAndRunButton_->setIcon(buildAndRunIcon);
        this->buildAndRunButton_->setIconSize(QSize(100, 100));
        this->buildAndRunButton_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(this->buildAndRunButton_, &QToolButton::clicked, this, &SettingsNavigation::bindBuildAndRundWidgets);

        // Append widgets to grid layout.
        this->navigationLayout_->addWidget(this->environmentButton_, 0, 1);
        this->navigationLayout_->addWidget(this->engineButton_, 0, 2);
        this->navigationLayout_->addWidget(this->buildAndRunButton_, 0, 3);

        this->navigationWidget_->setLayout(this->navigationLayout_);
        this->mainLayout_->addWidget(this->navigationWidget_);
    }

    void SettingsNavigation::bindEnvironmentWidgets()
    {

    }

    void SettingsNavigation::bindEngineWidgets()
    {

    }

    void SettingsNavigation::bindBuildAndRundWidgets()
    {

    }
}
