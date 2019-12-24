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
        delete environmentButton;
        delete engineButton;
        delete buildAndRunButton;
        delete navigationLayout;
        delete environmentSettings;
        delete engineSettings;
        delete buildAndRunSettings;
    }

    void SettingsNavigation::setupUi()
    {
        // Create settings widgets.
        this->environmentSettings = new EnvironmentSettings();
        this->engineSettings = new EngineSettings();
        this->buildAndRunSettings = new BuildAndRunSettings();

        // Bind widgets
        bindNavigationWidgets();
    }

    void SettingsNavigation::bindNavigationWidgets()
    {
        connect(this->backButton, &QPushButton::clicked, this, &SettingsNavigation::bindNavigationWidgets);

        this->navigationWidget = new QWidget();

        // Navigation layout.
        this->navigationLayout = new QGridLayout();

        this->environmentButton = new QToolButton();
        this->environmentButton->setText(QString("Environment"));
        this->environmentButton->setFixedSize(QSize(185, 185));
        this->environmentButton->setStyleSheet("padding: 15px;");
        QIcon environmentIcon;
        environmentIcon.addPixmap(QPixmap(":/rc/icons/environment.png"), QIcon::Normal, QIcon::Off);
        this->environmentButton->setIcon(environmentIcon);
        this->environmentButton->setIconSize(QSize(100, 100));
        this->environmentButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(this->environmentButton, &QToolButton::clicked, this, &SettingsNavigation::bindEnvironmentWidgets);

        this->engineButton = new QToolButton();
        this->engineButton->setText(QString("Engine"));
        this->engineButton->setFixedSize(QSize(185, 185));
        this->engineButton->setStyleSheet("padding: 15px;");
        QIcon engineIcon;
        engineIcon.addPixmap(QPixmap(":/rc/icons/welcome.png"), QIcon::Normal, QIcon::Off);
        this->engineButton->setIcon(engineIcon);
        this->engineButton->setIconSize(QSize(100, 100));
        this->engineButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(this->engineButton, &QToolButton::clicked, this, &SettingsNavigation::bindEngineWidgets);

        this->buildAndRunButton = new QToolButton();
        this->buildAndRunButton->setText(QString("Build && Run"));
        this->buildAndRunButton->setFixedSize(QSize(185, 185));
        this->buildAndRunButton->setStyleSheet("padding: 15px;");
        QIcon buildAndRunIcon;
        buildAndRunIcon.addPixmap(QPixmap(":/rc/icons/build.png"), QIcon::Normal, QIcon::Off);
        this->buildAndRunButton->setIcon(buildAndRunIcon);
        this->buildAndRunButton->setIconSize(QSize(100, 100));
        this->buildAndRunButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(this->buildAndRunButton, &QToolButton::clicked, this, &SettingsNavigation::bindBuildAndRundWidgets);

        // Append widgets to grid layout.
        this->navigationLayout->addWidget(this->environmentButton, 0, 1);
        this->navigationLayout->addWidget(this->engineButton, 0, 2);
        this->navigationLayout->addWidget(this->buildAndRunButton, 0, 3);

        this->navigationWidget->setLayout(this->navigationLayout);
        this->mainLayout->addWidget(this->navigationWidget);
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
