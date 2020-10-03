#ifndef NAGE_ENGINE_IO_INPUT_H_
#define NAGE_ENGINE_IO_INPUT_H_

#include "key.h"
#include "mousebutton.h"

#include <vector>
#include <algorithm>

namespace mr::nage
{
    // Input states (e.g. pressed, released).
    enum InputState
    {
        InputTriggered,
        InputPressed,
        InputReleased,
        InputRegistered,
        InputUnregistered,
        InputInvalid
    };

    // Helper struct - each input is a pair <T input, InputState state>
    // when InputState is Input::InputState and T is e.g. Keyboard or Mouse type.
    template <typename T>
    struct InputInstance
    {
        InputInstance(T _input, InputState _state)
            : input_(_input),
              state_(_state)
        {

        }

        bool operator==(const InputInstance& _rhs) const
        {
            return this->input == _rhs.input;
        }

        bool operator!=(const InputInstance& _rhs) const
        {
            return !operator==(_rhs);
        }

        T input_;
        InputState state_;
    };

    template <typename InputInstanceType>
    class Input
    {
    public:
        Input() {}

    protected:
        /* Find value in container
         *
         * @return std::vector::iterator - position iterator or end of container if not found.
         */
        template <class InputIt, class T>
        static constexpr InputIt find(InputIt _begin, InputIt _end, const T& _value)
        {
            for(; _begin != _end; ++_begin)
            {
                if(_begin->input_ == _value)
                    return _begin;
            }

            return _end;
        }

        /* Update input state.
         *
         * @param _instance - input instance to state update.
         */
        template <typename Instance>
        static void updateState(Instance& _instance)
        {
            switch(_instance.state_)
            {
                case InputState::InputRegistered:
                    _instance.state_ = InputState::InputTriggered;
                    break;
                case InputState::InputTriggered:
                    _instance.state_ = InputState::InputPressed;
                    break;
                case InputState::InputUnregistered:
                    _instance.state_ = InputState::InputReleased;
                    break;
                default:
                    break;
            }
        }

        /* Check if given input was released.
         *
         * @param _instance - input instance to check.
         * @return bool - input state == InputReleased
         */
        template <typename Instance>
        static bool checkReleased(Instance& _instance)
        {
            return _instance.state_ == InputState::InputReleased;
        }

        /* Updates input container - remove released inputs and update rest.
         *
         * @param _container - input container.
         */
        template <class Container>
        static void updateContainer(Container& _container)
        {
            typedef typename Container::iterator Iterator;
            typedef typename Container::value_type Type;

            // Remove "released" inputs from container.
            for(Iterator it = _container.begin(); it != _container.end();)
            {
                if(checkReleased<Type>(*it)) it = _container.erase(it);
                else it++;
            }

            // Update rest inputs states.
            for(auto& it : _container)
                updateState<Type>(it);
        }

        typedef std::vector<InputInstanceType> InputContainer;
    };
}

#endif // NAGE_ENGINE_IO_INPUT_H_
