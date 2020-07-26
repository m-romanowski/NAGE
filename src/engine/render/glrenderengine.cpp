#include "glrenderengine.h"

#include <QDebug>

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

    GLint GLRenderEngine::screenFrameBuffer() const
    {
        GLint frameBufferId;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &frameBufferId);

        return frameBufferId;
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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void GLRenderEngine::initializePreRenderEffects()
    {
        // Initialize scene effects.
        for(auto scene : mSceneManager->scenes())
        {
            scene.second->water()->setupWaterEffects();
            //scene.second->water()->setupFlowMapEffect(512, 512);
        }

        // Bind main frame buffer after effects initialization.
        FrameBuffer::unbind(mWindow, screenFrameBuffer());
    }

    void GLRenderEngine::render()
    {
        for(auto scene : mSceneManager->scenes())
            renderScene(scene.second);
    }

    void GLRenderEngine::enableClipPlane(int _idx)
    {
        glEnable(GL_CLIP_DISTANCE0 + _idx);
    }

    void GLRenderEngine::disableClipPlane(int _idx)
    {
        glDisable(GL_CLIP_DISTANCE0 + _idx);
    }

    void GLRenderEngine::renderScene(SceneNode* _node)
    {
        if(!_node)
            return;

        // Store main screen frame buffer id.
        // This is some of "bug" type - when we resize the render window
        // the main frame buffer id changes to the "random" id (different than zero which is default).
        GLint mainFrameBuffer = screenFrameBuffer();

        // Enable clip planes.
        enableClipPlane();

        Vector3f cameraPosition = _node->camera()->translation();

        float waterHeight = _node->water()->transform()->translation().y();
        float distance = 2 * (cameraPosition.y() - waterHeight);
        float cameraPitch = _node->camera()->pitch();

        // Water reflection effect.
        _node->water()->waterReflectionEffect()->bind();

        // Move camera to the bottom.
        cameraPosition.setY(cameraPosition.y() - distance);
        _node->camera()->setTranslation(cameraPosition);
        _node->camera()->rotate(-cameraPitch, Vector3f(1.0f, 0.0f, 0.0f));

        renderSceneObjects(_node, Vector4f(0.0f, 1.0f, 0.0f, -waterHeight));

        // Move camera to the original position.
        cameraPosition.setY(cameraPosition.y() + distance);
        _node->camera()->setTranslation(cameraPosition);
        _node->camera()->rotate(cameraPitch, Vector3f(1.0f, 0.0f, 0.0f));

        FrameBuffer::unbind(mWindow, mainFrameBuffer);

        // Water refraction effect.
        _node->water()->waterRefractionEffect()->bind();
        renderSceneObjects(_node, Vector4f(0.0f, -1.0f, 0.0f, waterHeight));

        disableClipPlane();
        FrameBuffer::unbind(mWindow, mainFrameBuffer);

        // Render "normal" scene.
        _node->renderAllComponents(Vector4f(0.0f, -1.0f, 0.0f, 1000.0f));
    }

    void GLRenderEngine::renderSceneObjects(SceneNode* _node, Vector4f _clipPlane)
    {
        clearScene();
        _node->renderSkybox();
        _node->renderModels(_clipPlane);
        _node->renderLights();
        _node->renderTerrain(_clipPlane);
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
