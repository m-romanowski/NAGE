#include "mouse.h"

namespace NAGE
{
    Mouse::InputContainer Mouse::mMouseContainer;
    Vector2f Mouse::mMousePreviousPosition;
    Vector2f Mouse::mMouseCurrentPosition;
    Vector2f Mouse::mMouseDelta;
    // X11 Mouse::mX11;

    Mouse::InputContainer::iterator Mouse::findMouseButton(MouseButton _button)
    {
        return find<InputContainer::iterator, MouseButton>(mMouseContainer.begin(),
            mMouseContainer.end(), _button);
    }

    void Mouse::update()
    {
        mMousePreviousPosition = mMouseCurrentPosition;
        mMouseCurrentPosition = Mouse::mousePosition();
        mMouseDelta = mMouseCurrentPosition - mMousePreviousPosition;

        updateContainer<InputContainer>(mMouseContainer);
    }

    InputState Mouse::mouseState(MouseButton _button)
    {
        InputContainer::iterator it = findMouseButton(_button);

        if(it != mMouseContainer.end())
            return it->state;

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
        // return mX11.cursorPosition();
        return Vector2f(QCursor::pos().x(), QCursor::pos().y());
    }

    Vector2f Mouse::mouseDelta()
    {
        return mMouseDelta;
    }

    void Mouse::registerMousePress(MouseButton _button)
    {
        InputContainer::iterator it = findMouseButton(_button);

        if(it == mMouseContainer.end())
            mMouseContainer.push_back(InputInstance(_button, InputState::InputRegistered));
    }

    void Mouse::registerMouseRelease(MouseButton _button)
    {
        InputContainer::iterator it = findMouseButton(_button);

        if(it != mMouseContainer.end())
            it->state = InputState::InputUnregistered;
    }
}
