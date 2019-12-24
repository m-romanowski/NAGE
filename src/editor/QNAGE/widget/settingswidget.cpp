#include "setingswidget.h"

namespace QNAGE
{
    SettingsWidget::SettingsWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        this->mainLayout = new QVBoxLayout();

        // Navigation
        this->settingsNavigation = new SettingsNavigation();
        this->mainLayout->addWidget(this->settingsNavigation);

        this->setLayout(this->mainLayout);
    }

    SettingsWidget::~SettingsWidget()
    {
        delete settingsNavigation;
        delete mainLayout;
    }
}
