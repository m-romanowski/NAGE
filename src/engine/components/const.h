#ifndef NAGE_CONST_H_
#define NAGE_CONST_H_

#include <string>

namespace NAGE
{
    // OpenGL version.
    constexpr unsigned int GL_CONTEXT_VERSION_MAJOR = 4;
    constexpr unsigned int GL_CONTEXT_VERSION_MINOR = 6;

    // Default camera settings.
    constexpr float cameraSensitivity = 0.2f;
    constexpr float cameraMovementSpeed = 0.1f;
}

#endif // NAGE_CONST_H_
