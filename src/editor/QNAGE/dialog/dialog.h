#ifndef QNAGE_DIALOG_DIALOG_H_
#define QNAGE_DIALOG_DIALOG_H_

#include "window/framelesswindow.h"
namespace mr::qnage
{
    class Dialog
        : public FramelessWindow
    {
    public:
        explicit Dialog(QWidget* _parent) : FramelessWindow(_parent, FRAMELESSWINDOW_EXIT_BUTTON) {}
        virtual ~Dialog() {}

    protected:
        virtual void setupUi() = 0;
    };
}

#endif // QNAGE_DIALOG_DIALOG_H_
