#ifndef NAGE_ENGINE_UTIL_RANDOM_H_
#define NAGE_ENGINE_UTIL_RANDOM_H_

#include <random>

namespace NAGE
{
    static thread_local std::mt19937 gen{std::random_device{}()};

    template<typename T>
    T random(T min, T max) {
        using dist = std::conditional_t<
            std::is_integral<T>::value,
            std::uniform_int_distribution<T>,
            std::uniform_real_distribution<T>
        >;

        return dist{min, max}(gen);
    }
}

#endif // NAGE_ENGINE_UTIL_RANDOM_H_
