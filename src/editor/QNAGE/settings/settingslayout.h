#ifndef QNAGE_SETTINGS_SETTINGSLAYOUT_H_
#define QNAGE_SETTINGS_SETTINGSLAYOUT_H_

#include "ui/custombutton.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>

namespace QNAGE
{
    // Interface for other settings layouts.
    class SettingsLayout : public QWidget
    {
        Q_OBJECT

    public:
        explicit SettingsLayout(QWidget* _parent = nullptr);
        virtual ~SettingsLayout();

        virtual void setupUi() = 0;
        static void clearLayout(QLayout* _layout);
        static void removeWidgetAt(QLayout* _layout, int _idx);

        QVBoxLayout* mainLayout;
        CustomButton* backButton;
    };
}

#endif // QNAGE_SETTINGS_SETTINGSLAYOUT_H_
