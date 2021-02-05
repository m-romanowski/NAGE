#ifndef QNAGE_UI_CLICKABLELABEL_H_
#define QNAGE_UI_CLICKABLELABEL_H_

#include <QLabel>

namespace mr::qnage
{
    class ClickableLabel
        : public QLabel
    {
        Q_OBJECT
    
    public:
        explicit ClickableLabel(QWidget* _parent = nullptr);
    
    signals:
        void clicked();

    protected:
        void mousePressEvent(QMouseEvent* _event);
    };
}

#endif // QNAGE_UI_CLICKABLELABEL_H_
