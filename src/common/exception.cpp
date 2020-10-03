#include "exception.h"

namespace mr::nage
{
    Exception::Exception(const std::string _msg)
        : message(_msg)
    {

    }

    /* Return the message.
     */
    const char* Exception::what() const noexcept
    {
        return this->message.c_str();
    }
}
