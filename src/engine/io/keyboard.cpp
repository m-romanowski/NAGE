#include "keyboard.h"

namespace NAGE
{
    Keyboard::InputContainer Keyboard::keyContainer_;

    void Keyboard::update()
    {
        updateContainer<InputContainer>(keyContainer_);
    }

    InputState Keyboard::keyState(Key _key)
    {
        InputContainer::iterator it = findKey(_key);

        if(it != keyContainer_.end())
            return it->state_;

        return InputState::InputInvalid;
    }

    bool Keyboard::keyTriggered(Key _key)
    {
        return keyState(_key) == InputState::InputTriggered;
    }

    bool Keyboard::keyPressed(Key _key)
    {
        return keyState(_key) == InputState::InputPressed;
    }

    bool Keyboard::keyReleased(Key _key)
    {
        return keyState(_key) == InputState::InputReleased;
    }

    void Keyboard::registerKeyPress(Key _key)
    {
        InputContainer::iterator it = findKey(_key);

        if(it == keyContainer_.end())
            keyContainer_.push_back(InputInstance(_key, InputState::InputRegistered));
    }

    void Keyboard::registerKeyRelease(Key _key)
    {
        InputContainer::iterator it = findKey(_key);

        if(it != keyContainer_.end())
            it->state_ = InputState::InputUnregistered;
    }

    Keyboard::InputContainer::iterator Keyboard::findKey(Key _key)
    {
        return find<InputContainer::iterator, Key>(keyContainer_.begin(), keyContainer_.end(), _key);
    }
}
