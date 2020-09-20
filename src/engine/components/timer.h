#ifndef NAGE_ENGINE_COMPONENTS_TIMER_H_
#define NAGE_ENGINE_COMPONENTS_TIMER_H_

#include <chrono>
#include <thread>
#include <functional>

namespace NAGE
{
    class Timer
    {
    public:
        typedef std::chrono::high_resolution_clock Clock;
        typedef std::chrono::milliseconds ms;

        Timer();

        void start();
        void stop();
        bool isActive();
        Clock::duration timeElapsed() const;
        ms timeElapsedMs() const;
        void setTimeout(std::function<void(void)> _function, long _msDelay);
        void setInterval(std::function<void(void)> _function, long _msInterval);

        static Clock::time_point now();

    private:
        Clock::time_point epoch_;
        bool flag_; // 1 - active, 0 - inactive.
    };
}

#endif // NAGE_ENGINE_COMPONENTS_TIMER_H_
