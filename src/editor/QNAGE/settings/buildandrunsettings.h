#ifndef QNAGE_SETTINGS_BUILDANDRUNSETTINGS_H_
#define QNAGE_SETTINGS_BUILDANDRUNSETTINGS_H_

#include "settingslayout.h"
#include <QLabel>

namespace QNAGE
{
    class BuildAndRunSettings : public SettingsLayout
    {
    public:
        BuildAndRunSettings(QWidget* _parent = nullptr);
        ~BuildAndRunSettings();

        virtual void setupUi();

    private:
        QLabel* label;
    };
}

#endif // QNAGE_SETTINGS_BUILDANDRUNSETTINGS_H_
