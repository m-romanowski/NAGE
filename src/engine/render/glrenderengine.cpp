#include "glrenderengine.h"

namespace mr::nage
{
    Projection GLRenderEngine::projection_;

    GLRenderEngine::GLRenderEngine(IWindow* _window)
        : window_(_window),
          sceneColor_(new Color)
    {

    }

    GLRenderEngine::~GLRenderEngine()
    {
        delete window_;
        delete sceneColor_;
    }

    IWindow* GLRenderEngine::window()
    {
        return window_;
    }

    Color* GLRenderEngine::sceneColor()
    {
        return sceneColor_;
    }

    GLint GLRenderEngine::screenFrameBuffer() const
    {
        GLint frameBufferId;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &frameBufferId);

        // TODO: change to `frameBufferId`.
        return 0;
    }

    void GLRenderEngine::clearScene()
    {
        glClearColor(sceneColor_->red(), sceneColor_->green(), sceneColor_->blue(),
            sceneColor_->alpha());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderEngine::initialize()
    {
        // Initialize window.
        window_->initialize();

        if(window_->initialized())
        {
            // OpenGL initial settings.
            glEnable(GL_DEPTH_TEST);
//            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }

        Log::log("API: OpenGL " + apiVersion());
    }

    void GLRenderEngine::initializePreRenderEffects()
    {
        // Initialize scene effects.
        for(auto scene : sceneManager_->scenes())
        {
            for(auto water : waterSources(scene.second->renderableObjects()))
            {
                water->setupWaterEffects();
                //scene.second->water()->setupFlowMapEffect(512, 512);
            }
        }

        // Bind main frame buffer after effects initialization.
        FrameBuffer::unbind(window_, screenFrameBuffer());
    }

    void GLRenderEngine::preRender()
    {
        // Poll next window event.
        window_->nextEvent();
    }

    void GLRenderEngine::render()
    {
        clearScene();

        for(auto scene : sceneManager_->scenes())
            renderScene(scene.second);

        window_->update();
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

        GLRenderEngine::RenderableContainer objectsToRender = sortByDepth(_node->renderableObjects());
        Camera* camera = _node->camera();

        // Setup optional water reflection / refraction effect.
        setWaterEffect(objectsToRender, camera);

        // Render "normal" scene.
        renderFullScene(objectsToRender, camera, Vector4f(0.0f, -1.0f, 0.0f, 1000.0f));
    }

    void GLRenderEngine::renderBaseScene(const GLRenderEngine::RenderableContainer& _renderableComponents, Camera* _camera, const Vector4f _clipPlane)
    {
        clearScene();

        std::vector<ILight*> lights = lightSources(_renderableComponents);
        for(auto renderable : _renderableComponents)
        {
            if(!renderable->isWaterSource())
                renderObject(renderable, _camera, _clipPlane, lights);
        }
    }

    void GLRenderEngine::renderFullScene(const GLRenderEngine::RenderableContainer& _renderableObjects, Camera* _camera, const Vector4f _clipPlane)
    {
        clearScene();

        std::vector<ILight*> lights = lightSources(_renderableObjects);
        for(auto renderable : _renderableObjects)
        {
            renderObject(renderable, _camera, _clipPlane, lights);
        }
    }


    void GLRenderEngine::renderObject(RenderableObject* _renderable, Camera* _camera, const Vector4f _clipPlane, const std::vector<ILight*>& _lightSource)
    {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        if(!_renderable->isLightSource())
            _renderable->applyLights(_camera, _lightSource);

        _renderable->useMaterials();
        _renderable->bindTextures();
        _renderable->draw(_camera, _clipPlane);
    }

    void GLRenderEngine::setWaterEffect(const GLRenderEngine::RenderableContainer& _renderableObjects, Camera* _camera)
    {
        // Store main screen frame buffer id.
        //
        // TODO: This is some of "bug" type - when we resize the render window
        // the main frame buffer id changes to the "random" id (different than zero which is default).
        GLint mainFrameBuffer = screenFrameBuffer();

        // Enable clip planes.
        enableClipPlane();

        for(auto water : waterSources(_renderableObjects))
        {
            Vector3f cameraPosition = _camera->translation();

            float waterHeight = 0.0f;
            float distance = 0.0f;
            float cameraPitch = _camera->pitch();

            waterHeight = water->transformation()->translation().y();
            distance = 2 * (cameraPosition.y() - waterHeight);

            // Water reflection effect.
            water->waterReflectionEffect()->bind();

            // Move camera to the bottom.
            cameraPosition.setY(cameraPosition.y() - distance);
            _camera->setTranslation(cameraPosition);
            _camera->rotate(-cameraPitch, Vector3f(1.0f, 0.0f, 0.0f));

            renderBaseScene(_renderableObjects, _camera, Vector4f(0.0f, 1.0f, 0.0f, -waterHeight));

            // Move camera to the original position.
            cameraPosition.setY(cameraPosition.y() + distance);
            _camera->setTranslation(cameraPosition);
            _camera->rotate(cameraPitch, Vector3f(1.0f, 0.0f, 0.0f));

            FrameBuffer::unbind(window_, mainFrameBuffer);

            // Water refraction effect.
            water->waterRefractionEffect()->bind();
            renderBaseScene(_renderableObjects, _camera, Vector4f(0.0f, -1.0f, 0.0f, waterHeight));

            disableClipPlane();
            FrameBuffer::unbind(window_, mainFrameBuffer);
        }
    }

    std::vector<ILight*> GLRenderEngine::lightSources(const GLRenderEngine::RenderableContainer& _renderableObjects) const
    {
        std::vector<ILight*> result;
        for(auto renderable : _renderableObjects)
        {
            if(renderable->isLightSource())
                result.push_back(dynamic_cast<ILight*>(renderable));
        }

        return result;
    }

    std::vector<IWater*> GLRenderEngine::waterSources(const GLRenderEngine::RenderableContainer& _renderableObjects) const
    {
        std::vector<IWater*> result;
        for(auto renderable : _renderableObjects)
        {
            if(renderable->isWaterSource())
                result.push_back(dynamic_cast<IWater*>(renderable));
        }

        return result;
    }

    GLRenderEngine::RenderableContainer GLRenderEngine::sortByDepth(GLRenderEngine::RenderableContainer _renderableObjects) const
    {
        std::sort(_renderableObjects.begin(), _renderableObjects.end(), [](const RenderableObject* _first, const RenderableObject* _second) {
            return _first->depth() > _second->depth();
        });

        return _renderableObjects;
    }

    std::string GLRenderEngine::apiVersion() const
    {
        return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }

    Projection& GLRenderEngine::projection()
    {
        return projection_;
    }
}
