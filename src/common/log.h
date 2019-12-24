#ifndef NAGE_COMMON_DEBUG_H_
#define NAGE_COMMON_DEBUG_H_

#include "exception.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>

namespace NAGE
{
    class Log
    {
    public:
        Log() {}

        // Debug log
        static void log(const std::string& _message);
        static std::string getCurrentTime();

        template <typename T>
        static void log(const std::string& _message, const std::vector<T>& _additionalMessages)
        {
            std::cout << "[LOG] " << _message << " ";

            for(const auto& message : _additionalMessages)
                std::cout << message << " ";

            std::cout << std::endl;
        }

        // Debug error
        static void error(const std::string& _message);

        // Debug critical errror
        static void critical(const std::string& _message);
    };
}

#endif // NAGE_COMMON_DEBUG_H_
