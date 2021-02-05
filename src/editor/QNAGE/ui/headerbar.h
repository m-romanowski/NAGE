#ifndef QNAGE_UI_HEADERBAR_H_
#define QNAGE_UI_HEADERBAR_H_

#include <QLabel>

namespace mr::qnage
{
    class HeaderBar
        : public QLabel
    {
        Q_OBJECT

    public:
        explicit HeaderBar(const QString _title, QWidget* _parent = nullptr)
            : QLabel(_parent)
        {
            this->setText(_title);
            this->setFixedHeight(35);
            this->setObjectName("header-bar");
        }
    };
}

#endif // QNAGE_UI_HEADERBAR_H_
