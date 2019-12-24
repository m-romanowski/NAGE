#ifndef QNAGE_SETTINGS_ENVIRONMENTSETTINGS_H_
#define QNAGE_SETTINGS_ENVIRONMENTSETTINGS_H_

#include "settingslayout.h"
#include <QLabel>

namespace QNAGE
{
    class EnvironmentSettings : public SettingsLayout
    {
    public:
        EnvironmentSettings(QWidget* _parent = nullptr);
        ~EnvironmentSettings();

        virtual void setupUi();

    private:
        QLabel* label;
    };
}

#endif // QNAGE_SETTINGS_ENVIRONMENTSETTINGS_H_
