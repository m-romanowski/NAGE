#ifndef QNAGE_UI_TABBAR_H_
#define QNAGE_UI_TABBAR_H_

#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabBar>
#include <QPaintEvent>
#include <QSize>
#include <QPoint>
#include <QRect>

namespace QNAGE
{
    class TabBar : public QTabBar
    {
    public:
        TabBar();
        QSize tabSizeHint(int _index) const override;

    protected:
        void paintEvent(QPaintEvent* _event) override;
    };
}

#endif // QNAGE_UI_TABBAR_H_
