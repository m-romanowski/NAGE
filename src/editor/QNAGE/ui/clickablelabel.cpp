#include "clickablelabel.h"

namespace mr::qnage
{
    ClickableLabel::ClickableLabel(QWidget* _parent)
        : QLabel(_parent)
    {
        this->setCursor(Qt::OpenHandCursor);
    }

    void ClickableLabel::mousePressEvent(QMouseEvent* _event)
    {
        emit clicked();
    }
}
