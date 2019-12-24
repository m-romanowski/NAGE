#include "tabbar.h"

namespace QNAGE
{
    TabBar::TabBar()
    {

    }

    QSize TabBar::tabSizeHint(int _index) const
    {
        QSize size = QTabBar::tabSizeHint(_index);
        size.transpose();

        return size;
    }

    void TabBar::paintEvent(QPaintEvent* _event)
    {
        Q_UNUSED(_event);

        QStylePainter painter(this);
        QStyleOptionTab opt;

        for(int i = 0; i < count(); i++)
        {
            initStyleOption(&opt, i);
            painter.drawControl(QStyle::CE_TabBarTabShape, opt);
            painter.save();

            QSize size = opt.rect.size();
            size.transpose();

            QRect rect(QPoint(), size);
            rect.moveCenter(opt.rect.center());
            opt.rect = rect;

            QPoint point = tabRect(i).center();
            painter.translate(point);
            painter.rotate(90);
            painter.translate(-point);
            painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
            painter.restore();
        }
    }
}
