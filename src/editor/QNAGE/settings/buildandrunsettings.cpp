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
        this->label_ = new QLabel(tr("Build && Run"));
        this->mainLayout_->addWidget(this->label_);
    }
}
