#ifndef NAGE_ENGINE_CORE_IGAME_H_
#define NAGE_ENGINE_CORE_IGAME_H_

#include "engine/components/types.h"
#include "engine/core/coreengine.h"
#include "engine/render/irenderengine.h"
#include "engine/render/glrenderengine.h"
#include "scene/scenemanager.h"

#include <string>

namespace mr::nage
{
    /* Abstract class - interface for a new game.
     */
    class IGame
    {
    public:
        IGame(FpsLimit _limit = FpsLimit::FPS_60);
        virtual ~IGame();

        // Getters
        CoreEngine* engine();
        SceneManager* sceneManager();

        // Setters
        void setEngine(CoreEngine* _engine);

        virtual void initializeScene() = 0;
        virtual void ioEventsSupplier() = 0;

        void initializeComponents(EngineType _type, IWindow* _window);
        void launch();

    protected:
        CoreEngine* coreEngine_;
    };
}

#endif // NAGE_ENGINE_CORE_IGAME_H_
