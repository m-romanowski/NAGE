#ifndef NAGE_ENGINE_RENDER_GLRENDERENGINE_H_
#define NAGE_ENGINE_RENDER_GLRENDERENGINE_H_

#ifndef GL_API
    #define GL_API
#endif // GL_API

#include "projection.h"
#include "engine/io/iwindow.h"
#include "engine/components/const.h"
#include "engine/render/color.h"
#include "engine/render/irenderengine.h"

#include <vector>

namespace NAGE
{
    class GLRenderEngine : public IRenderEngine
    {
    public:
        GLRenderEngine(IWindow* _window = nullptr);
        virtual ~GLRenderEngine() override;

        // Getters
        IWindow* window();
        Color* sceneColor();

        // Setters
        void setSceneColor(Color* _color);
        void setSceneColor(float _r, float _g, float _b, float _a = 1.0f);

        virtual void render() override;
        virtual void initialize() override;
        virtual std::string apiVersion() const override;
        // GLFWwindow* glfwWwindow() const;

        void clearScene();
        static Projection& projection();

    private:
        IWindow* mWindow;
        Color* mSceneColor;
        static Projection mProjection;
    };
}

#endif // NAGE_ENGINE_RENDER_GLRENDERENGINE_H_
