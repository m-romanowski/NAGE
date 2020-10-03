#ifndef QNAGE_SETTINGS_ENGINESETTINGS_H_
#define QNAGE_SETTINGS_ENGINESETTINGS_H_

#include "settingslayout.h"
#include <QLabel>

namespace mr::qnage
{
    class EngineSettings : public SettingsLayout
    {
    public:
        EngineSettings(QWidget* _parent = nullptr);
        ~EngineSettings();

        virtual void setupUi();

    private:
        QLabel* label_;
    };
}

#endif // QNAGE_SETTINGS_ENGINESETTINGS_H_
