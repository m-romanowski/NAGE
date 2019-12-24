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

namespace NAGE
{
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
        void initialize(IRenderEngine* _renderEngine);
        void run();
        void render();
        void stop();
        void startPollingEvents();

    protected:
        // Engine sub-components
        IRenderEngine* mRenderEngine;

        // Engine settings
        FpsLimit mFpsLimit;
        StatusCode mStatus;
        bool mDisplayFPS;
    };
}

#endif // NAGE_ENGINE_CORE_COREENGINE_H_
