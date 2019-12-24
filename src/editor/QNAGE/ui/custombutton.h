#ifndef QNAGE_UI_CUSTOMBUTTON_H_
#define QNAGE_UI_CUSTOMBUTTON_H_

#include <QPushButton>
#include <QIcon>
#include <QVariant>

namespace QNAGE
{
    class CustomButton : public QPushButton
    {
    public:
        explicit CustomButton(QWidget* _parent = nullptr);
        virtual ~CustomButton();

        // Setters
        void setCustomIcon(const QIcon _icon, QSize _size = QSize(20, 20));
        void setCustomText(const QString& _text = "");
        void setCustomName(const QString& _name = "custom-button");
        void setCustomMinimumSize(const QSize _size);
        void setCustomMaximumSize(const QSize _size);
        void setCustomSize(const QSize _size);
    };
}

#endif // QNAGE_UI_CUSTOMBUTTON_H_
