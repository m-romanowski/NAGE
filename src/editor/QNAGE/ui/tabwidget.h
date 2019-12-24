#ifndef QNAGE_UI_TABWIDGET_H_
#define QNAGE_UI_TABWIDGET_H_

#include "tabbar.h"
#include <QTabWidget>

namespace QNAGE
{
    class TabWidget : public QTabWidget
    {
    public:
        TabWidget(QWidget* _parent = nullptr);
    };
}

#endif // QNAGE_UI_TABWIDGET_H_
