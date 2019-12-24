#include "settingslayout.h"

namespace QNAGE
{
    SettingsLayout::SettingsLayout(QWidget* _parent)
        : QWidget(_parent),
          mainLayout(new QVBoxLayout())
    {
        this->backButton = new CustomButton();
        QIcon backButtonIcon;
        backButtonIcon.addPixmap(QPixmap(":/rc/icons/left-arrow.png"), QIcon::Normal, QIcon::Off);
        this->backButton->setCustomIcon(backButtonIcon, QSize(23, 23));

        this->setLayout(this->mainLayout);
    }

    SettingsLayout::~SettingsLayout()
    {
        delete backButton;
        delete mainLayout;
    }

    void SettingsLayout::clearLayout(QLayout* _layout)
    {
        for(int i = 0; i < _layout->count(); i++)
        {
            // Clear widgets
            QWidget* widget = _layout->takeAt(i)->widget();
            if(widget != nullptr)
                _layout->removeWidget(widget);

            // Clear child layouts
            QLayout* childLayout = _layout->layout();
            if(childLayout != nullptr)
                SettingsLayout::clearLayout(childLayout);

            delete widget;
        }
    }

    void SettingsLayout::removeWidgetAt(QLayout* _layout, int _idx)
    {
        QWidget* widget = _layout->takeAt(_idx)->widget();
        _layout->removeWidget(widget);

        delete widget;
    }
}
