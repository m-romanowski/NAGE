#ifndef NAGE_ENGINE_IO_MOUSE_H_
#define NAGE_ENGINE_IO_MOUSE_H_

// #include "X11.h"
#include "input.h"
#include "engine/math/NAGEMath/nagemathvector.h"

namespace mr::nage
{
    class Mouse : public Input<InputInstance<MouseButton>>
    {
    public:
        Mouse() {}

        static InputState mouseState(MouseButton _button);
        static bool mouseButtonTriggered(MouseButton _button);
        static bool mouseButtonPressed(MouseButton _button);
        static bool mouseButtonReleased(MouseButton _button);
        static Vector2f mousePosition();
        static Vector2f mouseDelta();

        static void registerMousePress(MouseButton _button);
        static void registerMouseRelease(MouseButton _button);
        static void registerMouseMove(const Vector2f _movePosition);
        static void update();

    private:
        // Helper function
        static InputContainer::iterator findMouseButton(MouseButton _button);

        static InputContainer mouseContainer_;
        static Vector2f mousePreviousPosition_;
        static Vector2f mouseCurrentPosition_;
        static Vector2f mouseDelta_;
        static Vector2f mouseCursorPosition_;
    };
}

#endif // NAGE_ENGINE_IO_MOUSE_H_
