#include "errormanager.h"

namespace NAGE
{
    const char* ErrorManager::name() const noexcept
    {
        return "ErrorManager api";
    }

    std::string ErrorManager::message(int _ev) const
    {
        switch (static_cast<ERROR>(_ev))
        {
            // ENGINE
            case ERROR::ENGINE_FAILED_GAME_INITIALIZATION: return "Failed game initialization";
            // GLFW
            case ERROR::GLFW_FAILED_CREATE_WINDOW: return "Failed to create GLFW window.";
            case ERROR::GLFW_FAILED_INITIALIZATION: return "Failed to initalize GLFW.";
            // GLAD
            case ERROR::FAILED_GLAD_INITIALIZATION: return "Failed to initialize GLAD.";
            // SHADER
            case ERROR::SHADER_FAILED_LINKING: return "Failed to link shader program.";
            case ERROR::SHADER_FAILED_FILE_READ: return "Failed to open shader file.";
            case ERROR::SHADER_FAILED_COMPILATION: return "Failed shader compilation.";
            case ERROR::SHADER_UNEXPECTED_TYPE: return "Unexpected shader type.";
            case ERROR::SHADER_FAILED_TO_FIND_PROGRAM: return "Failed to find shader program.";
            // SCENE
            case ERROR::SCENE_FAILED_TO_FIND_KEY: return "Failed to find key. Check if given key exists";
            case ERROR::SCENE_FAILED_TO_ADD_MODEL: return "Failed to add a new model to scene. Check if given key already not exists.";
            case ERROR::SCENE_FAILED_TO_ADD_LIGHT: return "Failed to add a new ligth to scene. Check if given key already not exists.";
            case ERROR::SCENE_FAILED_TO_ADD_CAMERA: return "Failed to add a new camera to scene. Check if given key already not exists.";
            case ERROR::SCENEMANAGER_FAILED_TO_ADD_NODE: return "Failed to add a new scene node. Check if given key exists";
            // X11
            case ERROR::X11_FAILED_DISPLAY_INITIALIZATION: return "Failed X11 display initialization";
            case ERROR::X11_FAILED_CURSOR_DETECTION: return "An error occured detecting the mouse position";
            // SKYBOX
            case ERROR::SKYBOX_FAILED_TO_LOAD_CUBMAP_TEXTURE: return "Failed to load skybox cube texture";
        }

        // Default return if error type not exists.
        return "Unknown error type";
    }

    bool ErrorManager::equivalent(const std::error_code& _code, int _condition) const noexcept
    {
        return *this == _code.category() &&
            static_cast<int>(default_error_condition(_code.value()).value()) == _condition;
    }
}
