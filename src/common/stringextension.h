#ifndef NAGE_COMMON_STRING_EXTENSION_H_
#define NAGE_COMMON_STRING_EXTENSION_H_

#include <string>
#include <vector>
#include <cstring>

namespace mr::nage
{
    class StringExtension
    {
    public:
        static std::vector<std::string> split(std::string str, std::string sep)
        {
            char* cstr = const_cast<char*>(str.c_str());
            char* current;

            std::vector<std::string> arr;
            current = strtok(cstr, sep.c_str());

            while(current != nullptr)
            {
                arr.push_back(current);
                current = strtok(nullptr, sep.c_str());
            }

            return arr;
        }

        static std::vector<std::string> removeEmptyStrings(std::vector<std::string> str)
        {
            std::vector<std::string> result;

            for(unsigned int i = 0; i < str.size(); i++)
                if(str[i] != "")
                    result.push_back(str[i]);

            return result;
        }
    };
}

#endif // NAGE_COMMON_STRING_EXTENSION_H_
