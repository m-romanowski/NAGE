#ifndef GLWRAPPER_H_
#define GLWRAPPER_H_

#include "glad/glad.h"

#include <vector>
#include <cstddef>

namespace NAGE
{
    template <class T>
    inline void nage_glBufferData(GLenum _target, const std::vector<T>& _v, GLenum _usage)
    {
        glBufferData(_target, _v.size() * sizeof(T), &_v[0], _usage);
    }
}

#endif // GLWRAPPER_H_
