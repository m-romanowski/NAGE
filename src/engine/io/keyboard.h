#ifndef NAGE_ENGINE_IO_KEYBOARD_H_
#define NAGE_ENGINE_IO_KEYBOARD_H_

#include "input.h"

namespace mr::nage
{
    class Keyboard : public Input<InputInstance<Key>>
    {
    public:
        Keyboard() {}

        static InputState keyState(Key _key);
        static bool keyTriggered(Key _key);
        static bool keyPressed(Key _key);
        static bool keyReleased(Key _key);

        static void registerKeyPress(Key _key);
        static void registerKeyRelease(Key _key);
        static void update();

    private:
        // Helper function
        static InputContainer::iterator findKey(Key _key);

        // Buttons states container.
        static InputContainer keyContainer_;
    };
}

#endif // NAGE_ENGINE_IO_KEYBOARD_H_
