#ifndef NAGE_COMMON_ERRORMANAGER_H_
#define NAGE_COMMON_ERRORMANAGER_H_

#include <system_error>
#include <string>

namespace mr::nage
{
    enum class ERROR
    {
        // ENGINE
        ENGINE_FAILED_GAME_INITIALIZATION = 1,
        // GLFW
        GLFW_FAILED_INITIALIZATION = 100,
        GLFW_FAILED_CREATE_WINDOW = 101,
        // GLAD
        FAILED_GLAD_INITIALIZATION = 200,
        // SHADER
        SHADER_FAILED_FILE_READ = 300,
        SHADER_FAILED_COMPILATION = 301,
        SHADER_FAILED_LINKING = 302,
        SHADER_UNEXPECTED_TYPE = 303,
        SHADER_FAILED_TO_FIND_PROGRAM = 304,
        // SCENE
        SCENE_FAILED_TO_FIND_KEY = 400,
        SCENE_FAILED_TO_ADD_MODEL = 401,
        SCENE_FAILED_TO_ADD_LIGHT = 402,
        SCENE_FAILED_TO_ADD_CAMERA = 403,
        SCENEMANAGER_FAILED_TO_ADD_NODE = 404,
        // X11
        X11_FAILED_DISPLAY_INITIALIZATION = 500,
        X11_FAILED_CURSOR_DETECTION = 501,
        // SKYBOX
        SKYBOX_FAILED_TO_LOAD_CUBMAP_TEXTURE = 600

    };

    class ErrorManager : public std::error_category
    {
    public:
        ErrorManager() {}

        virtual const char* name() const noexcept override;
        virtual std::string message(int _ev) const override;
        virtual bool equivalent(const std::error_code& _code,
            int _condition) const noexcept override;
    };

    // make_error_code overload to generate custom conditions:
    inline std::error_code make_error_code(const ERROR &e) {
        return std::error_code(static_cast<int>(e), ErrorManager());
    }
}

namespace std
{
    template <> struct is_error_code_enum<mr::nage::ERROR> : public true_type {};
}

#endif // NAGE_COMMON_ERRORMANAGER_H_
