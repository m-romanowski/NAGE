#ifndef NAGE_COMMON_DEBUG_H_
#define NAGE_COMMON_DEBUG_H_

#include "logcplus/src/logcplus.h"
#include "exception.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>

namespace mr::nage
{
    class Log
    {
    public:
        Log() = default;

        static void debug(const std::string& _message);
        static void error(const std::string& _message);
        static void fatal(const std::string& _message);

    private:
        static dev::marcinromanowski::logcplus::Logger* logger();
    };
}

#endif // NAGE_COMMON_DEBUG_H_
