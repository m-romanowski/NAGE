#include "glrenderengine.h"

namespace NAGE
{
    Projection GLRenderEngine::mProjection;

    GLRenderEngine::GLRenderEngine(IWindow* _window)
        : mWindow(_window),
          mSceneColor(new Color)
    {

    }

    GLRenderEngine::~GLRenderEngine()
    {
        delete mWindow;
        delete mSceneColor;
    }

    IWindow* GLRenderEngine::window()
    {
        return mWindow;
    }

    Color* GLRenderEngine::sceneColor()
    {
        return mSceneColor;
    }

    void GLRenderEngine::clearScene()
    {
        glClearColor(mSceneColor->red(), mSceneColor->green(), mSceneColor->blue(),
            mSceneColor->alpha());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderEngine::initialize()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        // If blending is enable remove "discard option" from fragment shader.
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void GLRenderEngine::render()
    {
        clearScene();

        for(auto scene : mSceneManager->scenes())
        {
            scene.second->renderSkybox();
            scene.second->renderModels();
            scene.second->renderLights();
            scene.second->renderTerrain();
        }
    }

    std::string GLRenderEngine::apiVersion() const
    {
        return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }

    Projection& GLRenderEngine::projection()
    {
        return mProjection;
    }

    /*GLFWwindow* GLRenderEngine::glfwWwindow() const
    {
        if(mWindow != nullptr)
            return mWindow->getGLFWwindow();

        return nullptr;
    }*/
}
