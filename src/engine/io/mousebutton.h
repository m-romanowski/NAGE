#ifndef NAGE_ENGINE_IO_MOUSEBUTTON_H_
#define NAGE_ENGINE_IO_MOUSEBUTTON_H_

namespace mr::nage
{
    enum MouseButton
    {
        MOUSE_LEFT_BUTTON = 0,
        MOUSE_RIGHT_BUTTON = 1,
        MOUSE_MIDDLE_BUTTON = 2,
        // QT support
        QEDITOR_MOUSE_LEFT_BUTTON = 1,
        QEDITOR_MOUSE_RIGHT_BUTTON = 2,
        QEDITOR_MOUSE_MIDDLE_BUTTON = 4,
        QEDITOR_XBUTTON1 = 8,
        QEDITOR_XBUTTON2 = 10
    };
}

#endif // NAGE_ENGINE_IO_MOUSEBUTTON_H_
