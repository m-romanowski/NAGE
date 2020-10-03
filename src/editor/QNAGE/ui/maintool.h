#ifndef QNAGE_UI_MAINTOOL_H_
#define QNAGE_UI_MAINTOOL_H_

#include "custombutton.h"

#include <QWidget>
#include <QVBoxLayout>

namespace mr::qnage
{
    class MainTool : public QWidget
    {
    public:
        MainTool(QWidget* _parent = nullptr);
        ~MainTool();

    private:
        QVBoxLayout* layout_;
        CustomButton* welcomeButton_;
    };
}

#endif // QNAGE_UI_MAINTOOL_H_
