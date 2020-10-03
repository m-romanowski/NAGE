#ifndef NAGE_ENGINE_UTIL_THREADPOOL_H_
#define NAGE_ENGINE_UTIL_THREADPOOL_H_

#include <vector>
#include <thread>

namespace mr::nage
{
    // Very basic and trivial thread pool (need to be remodel in the future).
    // Should not be used in production app!
    class ThreadPool
    {
    public:
        ThreadPool()
        {
            workers_.resize(std::thread::hardware_concurrency());
        }

        ThreadPool(unsigned int _size)
        {
            _size <= 0
                ? workers_.resize(std::thread::hardware_concurrency())
                : workers_.resize(_size);
        }

        ~ThreadPool()
        {
            // Wait for all running threads.
            for(auto&& worker : workers_)
            {
                if(worker.joinable())
                    worker.join();
            }
        }

        template <typename Job>
        void run(Job&& _job)
        {
            for(auto&& worker : workers_)
            {
                // Still running or waiting to join.
                if(worker.joinable())
                    continue;

                // Run the job in thread from the thread pool.
                worker = std::thread(_job);
                return;
            }

            for(auto&& worker : workers_)
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
        std::vector<std::thread> workers_;
    };
}

#endif // NAGE_ENGINE_UTIL_THREADPOOL_H_
