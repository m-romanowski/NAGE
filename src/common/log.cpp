#include "log.h"

namespace NAGE
{
    /* Get current timestamp - hh:mm:ss
     */
    std::string Log::getCurrentTime()
    {
        std::string hours, minutes, seconds;

        time_t currentTime = time(nullptr);
        tm* timePtr = localtime(&currentTime);

        hours = std::to_string(timePtr->tm_hour);
        minutes = std::to_string(timePtr->tm_min);
        seconds = std::to_string(timePtr->tm_sec);

        // If number belongs to <0, 9> add leading zero.
        if(timePtr->tm_hour >= 0 && timePtr->tm_hour < 10) hours = "0" + hours;
        if(timePtr->tm_min >= 0 && timePtr->tm_min < 10) minutes = "0" + minutes;
        if(timePtr->tm_sec >= 0 && timePtr->tm_sec < 10) seconds = "0" + seconds;

        return hours + ":" + minutes + ":" + seconds;
    }

    /* Debug log with a single message.
     */
    void Log::log(const std::string& _message)
    {
        std::cout << getCurrentTime() << " [LOG] " << _message << std::endl;
    }

    /* Debug error message.
     */
    void Log::error(const std::string& _message)
    {
        std::cout << getCurrentTime() << " [ERROR] " << _message << std::endl;
    }

    /* Debug critical message.
     */
    void Log::critical(const std::string& _message)
    {
        throw Exception(getCurrentTime() + " [CRITICAL] " + _message);
    }
}
