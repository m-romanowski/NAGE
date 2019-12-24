#ifndef NAGE_ENGINE_UTIL_STL_H_
#define NAGE_ENGINE_UTIL_STL_H_

#include <string>
#include <unordered_map>

namespace NAGE
{
    class STL_UTIL
    {
    public:
        STL_UTIL() {}

        // Check if the key exists in unordered_map (models, lights).
        template <typename T>
        static bool checkKey(std::unordered_map<std::string, T>& _data, const std::string& _key)
        {
            if(_data.find(_key) == _data.end())
                return false;

            return true;
        }
    };
}

#endif // NAGE_ENGINE_UTIL_STL_H_
