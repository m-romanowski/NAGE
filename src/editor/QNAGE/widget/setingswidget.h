#ifndef QNAGE_WIDGET_SETTINGSWIDGET_H_
#define QNAGE_WIDGET_SETTINGSWIDGET_H_

#include "settings/settingsnavigation.h"

#include <QWidget>
#include <QVBoxLayout>

namespace QNAGE
{
    class SettingsWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit SettingsWidget(QWidget* _parent = nullptr);
        ~SettingsWidget();

    private:
        QVBoxLayout* mainLayout;
        SettingsNavigation* settingsNavigation;
    };
}

#endif // QNAGE_WIDGET_SETTINGSWIDGET_H_
