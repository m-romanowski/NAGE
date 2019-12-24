#include "inputwrapper.h"

namespace QNAGE
{
    InputWrapper::InputWrapper()
    {

    }

    NAGE::Vector2f InputWrapper::mousePosition()
    {
        QPoint pos = QCursor::pos();
        return NAGE::Vector2f(pos.x(), pos.y());
    }
}
