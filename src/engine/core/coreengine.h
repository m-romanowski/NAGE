#ifndef NAGE_ENGINE_CORE_COREENGINE_H_
#define NAGE_ENGINE_CORE_COREENGINE_H_

#include "common/log.h"
#include "engine/components/const.h"
#include "engine/components/types.h"
#include "engine/io/mouse.h"
#include "engine/io/keyboard.h"
#include "engine/render/irenderengine.h"
#include "engine/render/glrenderengine.h"

#include <iostream>
#include <chrono>
#include <atomic>

namespace mr::nage
{
    class IGame;

    class CoreEngine
    {
        enum StatusCode
        {
            NotInitialized = -1,
            Stopped,
            Initialized,
            Running,
        };

    public:
        CoreEngine();
        ~CoreEngine();

        // Getters
        FpsLimit fpsLimit() const;
        bool displayFps() const;
        int statusCode() const;
        std::string status() const;
        IRenderEngine* renderEngine();
        std::chrono::milliseconds frameLockMS() const;

        // Setters
        void setRenderEngine(IRenderEngine* _renderEngine);
        void setFrameLimit(FpsLimit _limit = FpsLimit::FPS_Unlimited);

        // Engine management
        void initialize(IRenderEngine* _renderEngine, IGame* _game);
        void run();
        void stop();
        bool isRunning();

    protected:
        // Engine sub-components
        IRenderEngine* renderEngine_;
        IGame* game_;

        // Main loop thread
        std::thread mainWorker_;

        // Engine settings
        FpsLimit fpsLimit_;
        std::atomic<StatusCode> status_;
        bool displayFPS_;

    private:
        void render();
        void pollEvents();
    };
}

#endif // NAGE_ENGINE_CORE_COREENGINE_H_
