#ifndef QNAGE_DIALOG_DIALOG_H_
#define QNAGE_DIALOG_DIALOG_H_

namespace mr::qnage
{
    class Dialog
    {
    public:
        Dialog();
        virtual ~Dialog();

    protected:
        virtual void setupUi() = 0;
    };
}

#endif // QNAGE_DIALOG_DIALOG_H_
