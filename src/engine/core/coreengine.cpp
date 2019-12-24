#include "coreengine.h"

namespace NAGE
{
    CoreEngine::CoreEngine()
        : mFpsLimit(FpsLimit::FPS_60),
          mStatus(StatusCode::NotInitialized),
          mDisplayFPS(false)
    {

    }

    CoreEngine::~CoreEngine()
    {
        delete mRenderEngine;
    }

    FpsLimit CoreEngine::fpsLimit() const
    {
        return mFpsLimit;
    }

    bool CoreEngine::displayFps() const
    {
        return mDisplayFPS;
    }

    int CoreEngine::statusCode() const
    {
        return mStatus;
    }

    std::string CoreEngine::status() const
    {
        switch(mStatus)
        {
            case -1:
                Log::log("[STATUS] Engine not initialized");
                break;
            case 0:
                Log::log("[STATUS] Engine stopped");
                break;
            case 1:
                Log::log("[STATUS] Engine initialized");
                break;
            case 2:
                Log::log("[STATUS] Engine is running");
                break;
        }

        return "[STATUS] Undefined status";
    }

    IRenderEngine* CoreEngine::renderEngine()
    {
        return mRenderEngine;
    }

    std::chrono::milliseconds CoreEngine::frameLockMS() const
    {
        if(mFpsLimit == FpsLimit::FPS_Unlimited)
            return std::chrono::milliseconds(0);

        return std::chrono::milliseconds(std::chrono::milliseconds(1000 / mFpsLimit));
    }

    void CoreEngine::setRenderEngine(IRenderEngine* _renderEngine)
    {
        mRenderEngine = _renderEngine;
    }

    void CoreEngine::setFrameLimit(FpsLimit _limit)
    {
        mFpsLimit = _limit;
    }

    void CoreEngine::initialize(IRenderEngine* _renderEngine)
    {
        Log::log("Engine initialization...");

        mRenderEngine = _renderEngine;
        mRenderEngine->initialize();

        #ifdef GL_API
            Log::log("API: OpenGL " + mRenderEngine->apiVersion());
        #endif

        if(mFpsLimit == FpsLimit::FPS_Unlimited)
            Log::log("FPS lock: disabled");
        else
            Log::log("FPS lock: " + std::to_string(mFpsLimit) + " fps (~" +
                std::to_string(frameLockMS().count()) + " ms)");

        mStatus = StatusCode::Initialized;

        Log::log("Waiting for events...");
    }

    void CoreEngine::run()
    {
        if(mStatus != StatusCode::Initialized)
            return;

        mStatus = StatusCode::Running;
        render();
    }

    void CoreEngine::render()
    {
        if(mStatus != StatusCode::Running)
            return;

        mRenderEngine->render();
    }

    void CoreEngine::stop()
    {
        if(mStatus != StatusCode::Running)
            return;

        mStatus = StatusCode::Stopped;
    }

    void CoreEngine::startPollingEvents()
    {
        if(mStatus != StatusCode::Running)
            return;

        // Update inputs.
        Mouse::update();
        Keyboard::update();
    }
}
