#include "custombutton.h"

namespace mr::qnage
{
    CustomButton::CustomButton(QWidget* _parent)
        : QPushButton(_parent)
    {
        // Button properties
        this->setObjectName("custom-button");
        this->setProperty("class", "window-button");
        this->setStyleSheet("QPushButton { border: none; }");
        this->setMinimumSize(QSize(60, 30));
        this->setMaximumSize(QSize(60, 30));
        this->setText("");
    }

    CustomButton::~CustomButton()
    {

    }

    void CustomButton::setCustomIcon(const QIcon _icon, QSize _size)
    {
        this->setIcon(_icon);
        this->setIconSize(_size);
    }

    void CustomButton::setCustomText(const QString& _text)
    {
        this->setText(_text);
    }

    void CustomButton::setCustomName(const QString& _name)
    {
        this->setObjectName(_name);
    }

    void CustomButton::setCustomMinimumSize(const QSize _size)
    {
        this->setMinimumSize(_size);
    }

    void CustomButton::setCustomMaximumSize(const QSize _size)
    {
        this->setMaximumSize(_size);
    }

    void CustomButton::setCustomSize(const QSize _size)
    {
        this->setFixedSize(_size.width(), _size.height());
    }
}
