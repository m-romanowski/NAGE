#include "setingswidget.h"

namespace mr::qnage
{
    SettingsWidget::SettingsWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        this->mainLayout_ = new QVBoxLayout();

        // Navigation
        this->settingsNavigation_ = new SettingsNavigation();
        this->mainLayout_->addWidget(this->settingsNavigation_);

        this->setLayout(this->mainLayout_);
    }

    SettingsWidget::~SettingsWidget()
    {
        delete settingsNavigation_;
        delete mainLayout_;
    }
}
