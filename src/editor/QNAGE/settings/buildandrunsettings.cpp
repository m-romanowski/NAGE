#include "buildandrunsettings.h"

namespace QNAGE
{
    BuildAndRunSettings::BuildAndRunSettings(QWidget *_parent)
        : SettingsLayout(_parent)
    {

    }

    BuildAndRunSettings::~BuildAndRunSettings()
    {

    }

    void BuildAndRunSettings::setupUi()
    {
        this->label = new QLabel(tr("Build && Run"));
        this->mainLayout->addWidget(this->label);
    }
}
