#include "enginesettings.h"

namespace QNAGE
{
    EngineSettings::EngineSettings(QWidget* _parent)
        : SettingsLayout(_parent)
    {

    }

    EngineSettings::~EngineSettings()
    {

    }

    void EngineSettings::setupUi()
    {
        this->label = new QLabel(tr("Engine"));
        this->mainLayout->addWidget(this->label);
    }
}
