#ifndef NAGE_ENGINE_RENDER_GLRENDERENGINE_H_
#define NAGE_ENGINE_RENDER_GLRENDERENGINE_H_

#include "projection.h"
#include "engine/io/iwindow.h"
#include "engine/components/const.h"
#include "engine/render/color.h"
#include "engine/render/irenderengine.h"
#include "engine/world/water/iwater.h"

#include <stdexcept>

namespace mr::nage
{
    class GLRenderEngine
        : public IRenderEngine
    {
        typedef std::vector<RenderableObject*> RenderableContainer;

    public:
        GLRenderEngine(IWindow* _window = nullptr);
        virtual ~GLRenderEngine() override;

        // Getters
        IWindow* window();
        Color* sceneColor();

        // Setters
        void setSceneColor(Color* _color);
        void setSceneColor(float _r, float _g, float _b, float _a = 1.0f);

        virtual void initialize() override;
        virtual void initializePreRenderEffects() override;
        virtual void preRender() override;
        virtual void render() override;
        virtual std::string apiVersion() const override;
        GLint screenFrameBuffer() const;

        void clearScene();
        void enableClipPlane(int _idx = 0);
        void disableClipPlane(int _idx = 0);

        static Projection& projection();

    private:
        void renderScene(SceneNode* _node);
        void renderBaseScene(const RenderableContainer& _renderableObjects, Camera* _camera, const Vector4f _clipPlane);
        void renderFullScene(const RenderableContainer& _renderableObjects, Camera* _camera, const Vector4f _clipPlane);
        void renderObject(RenderableObject* _renderable, Camera* _camera, const Vector4f _clipPlane, const std::vector<ILight*>& _lightSource);
        void setWaterEffect(const RenderableContainer& _renderableObjects, Camera* _camera);
        std::vector<ILight*> lightSources(const RenderableContainer& _renderableObjects) const;
        std::vector<IWater*> waterSources(const RenderableContainer& _renderableObjects) const;
        RenderableContainer sortByDepth(RenderableContainer _renderableObjects) const;

        IWindow* window_;
        Color* sceneColor_;
        static Projection projection_;
    };
}

#endif // NAGE_ENGINE_RENDER_GLRENDERENGINE_H_
