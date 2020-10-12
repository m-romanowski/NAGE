#include "mouse.h"
#include "engine/components/const.h"

namespace mr::nage
{
    Mouse::InputContainer Mouse::mouseContainer_;
    Vector2f Mouse::mousePreviousPosition_;
    Vector2f Mouse::mouseCurrentPosition_;
    Vector2f Mouse::mouseDelta_;
    Vector2f Mouse::mouseCursorPosition_;

    Mouse::InputContainer::iterator Mouse::findMouseButton(MouseButton _button)
    {
        return find<InputContainer::iterator, MouseButton>(mouseContainer_.begin(),
            mouseContainer_.end(), _button);
    }

    void Mouse::update()
    {
        mousePreviousPosition_ = mouseCurrentPosition_;
        mouseCurrentPosition_ = Mouse::mousePosition();
        mouseDelta_ = mouseCurrentPosition_ - mousePreviousPosition_;

        updateContainer<InputContainer>(mouseContainer_);
    }

    InputState Mouse::mouseState(MouseButton _button)
    {
        InputContainer::iterator it = findMouseButton(_button);

        if(it != mouseContainer_.end())
            return it->state_;

        return InputState::InputInvalid;
    }

    bool Mouse::mouseButtonTriggered(MouseButton _button)
    {
        return mouseState(_button) == InputState::InputTriggered;
    }

    bool Mouse::mouseButtonPressed(MouseButton _button)
    {
        return mouseState(_button) == InputState::InputPressed;
    }

    bool Mouse::mouseButtonReleased(MouseButton _button)
    {
        return mouseState(_button) == InputState::InputReleased;
    }

    Vector2f Mouse::mousePosition()
    {
        return mouseCursorPosition_;
    }

    Vector2f Mouse::mouseDelta()
    {
        return mouseDelta_;
    }

    void Mouse::registerMousePress(MouseButton _button)
    {
        InputContainer::iterator it = findMouseButton(_button);

        if(it == mouseContainer_.end())
            mouseContainer_.push_back(InputInstance(_button, InputState::InputRegistered));
    }

    void Mouse::registerMouseRelease(MouseButton _button)
    {
        InputContainer::iterator it = findMouseButton(_button);

        if(it != mouseContainer_.end())
            it->state_ = InputState::InputUnregistered;
    }

    void Mouse::registerMouseMove(const Vector2f _movePosition)
    {
        mouseCursorPosition_ = _movePosition;
    }
}
