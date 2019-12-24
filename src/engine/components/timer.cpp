#include "timer.h"

namespace NAGE
{
    Timer::Timer()
        : mFlag(true)
    {

    }

    void Timer::start()
    {
        mEpoch = Clock::now();
    }

    void Timer::stop()
    {
        mFlag = false;
    }

    bool Timer::isActive()
    {
        return mFlag;
    }

    Timer::Clock::duration Timer::timeElapsed() const
    {
        return Clock::now() - mEpoch;
    }

    Timer::ms Timer::timeElapsedMs() const
    {
        return std::chrono::duration_cast<ms>(timeElapsed());
    }

    void Timer::setTimeout(std::function<void(void)> _function, long _msDelay)
    {
        std::thread([=]()
        {
            if(mFlag) return;

            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(_msDelay);
            std::this_thread::sleep_until(x);

            if(mFlag) return;

            _function();
        }).detach();
    }

    void Timer::setInterval(std::function<void(void)> _function, long _msInterval)
    {
        std::thread([=]()
        {
            while(mFlag)
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
