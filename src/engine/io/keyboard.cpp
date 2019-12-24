#include "keyboard.h"

namespace NAGE
{
    Keyboard::InputContainer Keyboard::keyContainer;

    void Keyboard::update()
    {
        updateContainer<InputContainer>(keyContainer);
    }

    InputState Keyboard::keyState(Key _key)
    {
        InputContainer::iterator it = findKey(_key);

        if(it != keyContainer.end())
            return it->state;

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

        if(it == keyContainer.end())
            keyContainer.push_back(InputInstance(_key, InputState::InputRegistered));
    }

    void Keyboard::registerKeyRelease(Key _key)
    {
        InputContainer::iterator it = findKey(_key);

        if(it != keyContainer.end())
            it->state = InputState::InputUnregistered;
    }

    Keyboard::InputContainer::iterator Keyboard::findKey(Key _key)
    {
        return find<InputContainer::iterator, Key>(keyContainer.begin(), keyContainer.end(), _key);
    }
}
