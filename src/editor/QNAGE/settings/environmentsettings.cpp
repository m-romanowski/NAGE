#include "environmentsettings.h"

namespace QNAGE
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
        this->mainLayout->addWidget(this->backButton);
    }
}
