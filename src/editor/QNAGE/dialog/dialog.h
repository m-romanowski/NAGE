#ifndef QNAGE_DIALOG_DIALOG_H_
#define QNAGE_DIALOG_DIALOG_H_

// #include "window/framelesswindow.h"

#include <QWidget>

namespace mr::qnage
{
    class Dialog
        : public QWidget
    {
    public:
        explicit Dialog(QWidget* _parent) : QWidget(_parent) {}
        virtual ~Dialog() {}

    protected:
        virtual void setupUi() = 0;
    };
}

#endif // QNAGE_DIALOG_DIALOG_H_
