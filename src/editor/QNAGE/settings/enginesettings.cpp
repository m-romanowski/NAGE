#include "enginesettings.h"

namespace mr::qnage
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
        this->label_ = new QLabel(tr("Engine"));
        this->mainLayout_->addWidget(this->label_);
    }
}
