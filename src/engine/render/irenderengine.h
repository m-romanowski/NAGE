#ifndef NAGE_ENGINE_RENDER_IRENDERENGINE_H_
#define NAGE_ENGINE_RENDER_IRENDERENGINE_H_

#include "engine/core/scene/scenemanager.h"
#include <string>

namespace NAGE
{
    /* Render engine interface (base class).
     */
    class IRenderEngine
    {
    public:
        IRenderEngine();
        virtual ~IRenderEngine();

        // Getters
        SceneManager* sceneManager();

        // Setters
        void setSceneManager(SceneManager* _manager);

        virtual void initialize() = 0; // Render engine initialization.
        virtual void render() = 0; // Render scene.
        virtual std::string apiVersion() const = 0; // Get using api version.

    protected:
        SceneManager* mSceneManager;
    };
}

#endif // NAGE_ENGINE_RENDER_IRENDERENGINE_H_
