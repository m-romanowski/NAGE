#ifndef NAGE_TYPES_H_
#define NAGE_TYPES_H_

namespace NAGE
{
    enum EngineType
    {
        OpenGL,
        Vulkan, // Unsupported
        DirectX // Unsupported
    };

    enum CameraType
    {
        FLY_CAMERA,
        FIRST_PERSON_CAMERA,
        THIRD_PERSON_CAMERA
    };

    enum TextureType
    {
        TEXTURE_2D,
        TEXTURE_3D // Unsupported
    };

    enum FpsLimit
    {
        FPS_Unlimited = 0,
        FPS_30 = 30,
        FPS_60 = 60,
        FPS_120 = 120,
        FPS_144 = 144,
        FPS_240 = 240
    };
}

#endif // NAGE_TYPES_H_
