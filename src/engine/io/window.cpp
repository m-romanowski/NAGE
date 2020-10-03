#include "engine/io/mouse.h"
#include "engine/io/keyboard.h"
#include "window.h"

namespace mr::nage
{
    Window::Window(int _width, int _height, const std::string& _title)
        : width_(_width),
          height_(_height),
          title_(_title)
    {

    }

    Window::~Window()
    {

    }

    void Window::initGLFW()
    {
        // Initialize GLFW.
        if (!glfwInit())
        {
            std::error_code code = ERROR::GLFW_FAILED_INITIALIZATION;
            Log::critical(code.message());
            glfwTerminate();
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_CONTEXT_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_CONTEXT_VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwSwapInterval(0);

    // For IOS.
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

        // Create window
        window_ = glfwCreateWindow(width_, height_, title_.c_str(),
            nullptr, nullptr);

        if (window_ == nullptr)
        {
            std::error_code code = ERROR::GLFW_FAILED_CREATE_WINDOW;
            Log::critical(code.message());
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window_);
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetFramebufferSizeCallback(window_, framebufferResizeCallback);
        glfwSetKeyCallback(window_, keyCallback);
        glfwSetMouseButtonCallback(window_, mouseButtonCallback);
        glfwSetScrollCallback(window_, scrollCallback);

        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::error_code code = ERROR::FAILED_GLAD_INITIALIZATION;
            Log::critical(code.message());
            return;
        }
    }

    void Window::framebufferResizeCallback(GLFWwindow* _window, int _width, int _height)
    {
        NAGE_UNUSED(_window);
        glViewport(0, 0, _width, _height);
    }

    void Window::keyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
    {
        NAGE_UNUSED(_window);
        NAGE_UNUSED(_scancode);
        NAGE_UNUSED(_mods);

        if(_action == GLFW_PRESS)
            nage::Keyboard::registerKeyPress(static_cast<Key>(_key));

        if(_action == GLFW_RELEASE)
            nage::Keyboard::registerKeyRelease(static_cast<Key>(_key));
    }

    void Window::mouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods)
    {
        NAGE_UNUSED(_window);
        NAGE_UNUSED(_mods);

        if(_action == GLFW_PRESS)
            nage::Mouse::registerMousePress(static_cast<MouseButton>(_button));

        if(_action == GLFW_RELEASE)
            nage::Mouse::registerMouseRelease(static_cast<MouseButton>(_button));
    }

    void Window::scrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset)
    {
        // TMP
        NAGE_UNUSED(_window);
        NAGE_UNUSED(_xOffset);
        NAGE_UNUSED(_yOffset);
    }

    void Window::closeWindow()
    {
        glfwWindowShouldClose(window_);
    }
}
