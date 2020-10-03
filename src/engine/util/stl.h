#ifndef NAGE_ENGINE_UTIL_STLUTIL_H_
#define NAGE_ENGINE_UTIL_STLUTIL_H_

#include <string>
#include <unordered_map>

namespace mr::nage
{
    class STLUTIL
    {
    public:
        STLUTIL() {}

        // Check if the key exists in unordered_map.
        template <typename T>
        static bool checkKey(std::unordered_map<std::string, T>& _data, const std::string& _key)
        {
            if(_data.find(_key) == _data.end())
                return false;

            return true;
        }
    };
}

#endif // NAGE_ENGINE_UTIL_STLUTIL_H_
