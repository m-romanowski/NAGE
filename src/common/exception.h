#ifndef NAGE_COMMON_EXCEPTION_H_
#define NAGE_COMMON_EXCEPTION_H_

#include <exception>
#include <string>

namespace mr::nage
{
    class Exception : public std::exception
    {
    public:
        Exception(const std::string _msg);
        virtual const char* what() const noexcept;

    private:
        const std::string message;
    };
}

#endif // NAGE_COMMON_EXCEPTION_H_
