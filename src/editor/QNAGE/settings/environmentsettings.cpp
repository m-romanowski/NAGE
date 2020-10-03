#include "environmentsettings.h"

namespace mr::qnage
{
    EnvironmentSettings::EnvironmentSettings(QWidget* _parent)
        : SettingsLayout(_parent)
    {

    }

    EnvironmentSettings::~EnvironmentSettings()
    {

    }

    void EnvironmentSettings::setupUi()
    {
        this->mainLayout_->addWidget(this->backButton_);
    }
}
