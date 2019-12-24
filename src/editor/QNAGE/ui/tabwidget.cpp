#include "tabwidget.h"

namespace QNAGE
{
    TabWidget::TabWidget(QWidget* _parent)
        : QTabWidget(_parent)
    {
        setTabBar(new TabBar());
        setTabPosition(QTabWidget::West);
    }
}
