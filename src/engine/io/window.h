#ifndef NAGE_ENGINE_RENDER_WINDOW_H_
#define NAGE_ENGINE_RENDER_WINDOW_H_

#include "glad/glad.h"
#include "glfw/include/glfw3.h"

#include "engine/components/const.h"
#include "common/log.h"
#include "common/macro.h"
#include "common/errormanager.h"
#include "engine/math/NAGEMath/nagemathvector.h"

#include <iostream>
#include <string>

namespace NAGE
{
    /* Window interface.
     *
     * TODO:
     *  - scroll event
     */
    class Window
    {
    public:
        Window(int _width = 800, int _height = 600,
            const std::string& _title = "undefined");
        ~Window();

        // Getters
        inline int getWidth() { return width; }
        inline int getHeight() { return height; }
        inline GLFWwindow* getGLFWwindow() { return window; }

        // Setters
        inline void setWidth(int _width) { width = _width; }
        inline void setHeight(int _height) { height = _height; }
        inline void setWindowTitle(const std::string& _title) { title = _title; }


        void initGLFW(); // Init glfw window.
        void closeWindow(); // Close glfw window.

        static bool initialized(); // GLFW window was initialized?
        static Vector2f cursorPosition(); // Get current window cursor position.

    private:
        // Resize window handler.
        static void framebufferResizeCallback(GLFWwindow* _window, int _width, int _height);
        // TODO: scrollCallback
        static void keyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
        static void mouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods);
        static void scrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset);

        GLFWwindow* window;
        int width;
        int height;
        std::string title;
    };
}

#endif // NAGE_ENGINE_RENDER_WINDOW_H_
