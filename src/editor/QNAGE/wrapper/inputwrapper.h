#ifndef QNAGE_WRAPPER_INPUTWRAPPER_H_
#define QNAGE_WRAPPER_INPUTWRAPPER_H_

#include "widget/glwidget.h"
#include "engine/input/input.h"

#include <QCursor>

namespace QNAGE
{
    class InputWrapper : public NAGE::Input
    {
    public:
        InputWrapper();

        static NAGE::Vector2f mousePosition();

    private:
        friend class GLWidget;
    };
}

#endif // QNAGE_WRAPPER_INPUTWRAPPER_H_
