#ifndef QNAGE_UI_MAINTOOL_H_
#define QNAGE_UI_MAINTOOL_H_

#include "custombutton.h"

#include <QWidget>
#include <QVBoxLayout>

namespace QNAGE
{
    class MainTool : public QWidget
    {
    public:
        MainTool(QWidget* _parent = nullptr);
        ~MainTool();

    private:
        QVBoxLayout* layout;
        CustomButton* welcomeButton;
    };
}

#endif // QNAGE_UI_MAINTOOL_H_
