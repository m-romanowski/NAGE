#include "log.h"

namespace mr::nage
{
    dev::marcinromanowski::logcplus::Logger* Log::logger()
    {
        return dev::marcinromanowski::logcplus::LogManager::getLogger();
    }

    void Log::debug(const std::string& _message)
    {
        logger()->debug(_message);
    }

    void Log::error(const std::string& _message)
    {
        logger()->error(_message);
    }

    void Log::fatal(const std::string& _message)
    {
        logger()->fatal(_message);
    }
}
