#ifndef QNAGE_SETTINGS_SETTINGSNAVIGATION_H_
#define QNAGE_SETTINGS_SETTINGSNAVIGATION_H_

#include "settingslayout.h"
#include "environmentsettings.h"
#include "enginesettings.h"
#include "buildandrunsettings.h"

#include <QGridLayout>
#include <QToolButton>
#include <QSize>
#include <QIcon>
#include <QDebug>

namespace QNAGE
{
    class SettingsNavigation : public SettingsLayout
    {
    public:
        SettingsNavigation(QWidget* _parent = nullptr);
        ~SettingsNavigation();

    private slots:
        void bindNavigationWidgets();
        void bindEnvironmentWidgets();
        void bindEngineWidgets();
        void bindBuildAndRundWidgets();

    private:
        virtual void setupUi();

        // Navigation Ui
        QWidget* navigationWidget;
        QGridLayout* navigationLayout;
        QToolButton* environmentButton;
        QToolButton* engineButton;
        QToolButton* buildAndRunButton;

        // Setting Ui
        EnvironmentSettings* environmentSettings;
        EngineSettings* engineSettings;
        BuildAndRunSettings* buildAndRunSettings;
    };
}

#endif // QNAGE_SETTINGS_SETTINGSNAVIGATION_H_
