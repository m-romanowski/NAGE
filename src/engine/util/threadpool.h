#ifndef NAGE_ENGINE_UTIL_THREADPOOL_H_
#define NAGE_ENGINE_UTIL_THREADPOOL_H_

#include <vector>
#include <thread>

namespace NAGE
{
    // Very basic and trivial thread pool (need to be remodel in the future).
    // Should not be used in production app!
    class ThreadPool
    {
    public:
        ThreadPool()
        {
            mWorkers.resize(std::thread::hardware_concurrency());
        }

        ThreadPool(unsigned int _size)
        {
            _size <= 0
                ? mWorkers.resize(std::thread::hardware_concurrency())
                : mWorkers.resize(_size);
        }

        ~ThreadPool()
        {
            // Wait for all running threads.
            for(auto&& worker : mWorkers)
            {
                if(worker.joinable())
                    worker.join();
            }
        }

        template <typename Job>
        void run(Job&& _job)
        {
            for(auto&& worker : mWorkers)
            {
                // Still running or waiting to join.
                if(worker.joinable())
                    continue;

                // Run the job in thread from the thread pool.
                worker = std::thread(_job);
                return;
            }

            for(auto&& worker : mWorkers)
            {
                // Not run or already joined.
                if(!worker.joinable())
                    continue;

                worker.join();
                worker = std::thread(_job);
                return;
            }
        }

    private:
        std::vector<std::thread> mWorkers;
    };
}

#endif // NAGE_ENGINE_UTIL_THREADPOOL_H_
