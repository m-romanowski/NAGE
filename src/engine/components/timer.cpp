#include "timer.h"

namespace NAGE
{
    Timer::Timer()
        : flag_(true)
    {

    }

    void Timer::start()
    {
        epoch_ = Clock::now();
    }

    void Timer::stop()
    {
        flag_ = false;
    }

    bool Timer::isActive()
    {
        return flag_;
    }

    Timer::Clock::duration Timer::timeElapsed() const
    {
        return Clock::now() - epoch_;
    }

    Timer::ms Timer::timeElapsedMs() const
    {
        return std::chrono::duration_cast<ms>(timeElapsed());
    }

    void Timer::setTimeout(std::function<void(void)> _function, long _msDelay)
    {
        std::thread([=]()
        {
            if(flag_)
                return;

            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(_msDelay);
            std::this_thread::sleep_until(x);

            if(flag_)
                return;

            _function();
        }).detach();
    }

    void Timer::setInterval(std::function<void(void)> _function, long _msInterval)
    {
        std::thread([=]()
        {
            while(flag_)
            {
                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(_msInterval);
                _function();
                std::this_thread::sleep_until(x);
            }
        }).detach();
    }

    Timer::Clock::time_point Timer::now()
    {
        return Clock::now();
    }
}
