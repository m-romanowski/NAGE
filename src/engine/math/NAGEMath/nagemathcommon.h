#ifndef NAGEMATHCOMMON_H
#define NAGEMATHCOMMON_H

#include <cassert>
#include <cmath>
#include <limits>
#include <algorithm>

#define assertm(exp, msg) assert(((void)msg, exp))

namespace mr::nage
{
    typedef unsigned int uint;

    inline float nage_toRadians(float _degrees)
    {
        return _degrees * static_cast<float>(M_PI / 180);
    }

    inline float nage_toDegrees(float _radians)
    {
        return _radians * static_cast<float>(180 / M_PI);
    }

    inline double nage_toRadians(double _degrees)
    {
        return _degrees * (M_PI / 180);
    }

    inline double nage_toDegrees(double _radians)
    {
        return _radians * (180 / M_PI);
    }

    // https://www.embeddeduse.com/2019/08/26/qt-compare-two-floats
    inline bool nage_floatCompare(float _f1, float _f2)
    {
        static constexpr auto epsilon = 1.0e-05f;

        if (std::abs(_f1 - _f2) <= epsilon)
            return true;

        return std::abs(_f1 - _f2) <= epsilon * std::max(std::abs(_f1), std::abs(_f2));
    }

    inline bool nage_doubleCompare(double _f1, double _f2)
    {
        static constexpr auto epsilon = 1.0e-12;

        if (std::abs(_f1 - _f2) <= epsilon)
            return true;

        return std::abs(_f1 - _f2) <= epsilon * std::max(std::abs(_f1), std::abs(_f2));
    }
}

#endif // NAGEMATHCOMMON_H
