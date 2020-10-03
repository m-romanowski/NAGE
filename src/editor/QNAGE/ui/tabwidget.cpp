#include "tabwidget.h"

namespace mr::qnage
{
    TabWidget::TabWidget(QWidget* _parent)
        : QTabWidget(_parent)
    {
        setTabBar(new TabBar());
        setTabPosition(QTabWidget::West);
    }
}
