#include "coreengine.h"

namespace mr::nage
{
    CoreEngine::CoreEngine()
        : fpsLimit_(FpsLimit::FPS_60),
          status_(StatusCode::NotInitialized),
          displayFPS_(false)
    {

    }

    CoreEngine::~CoreEngine()
    {
        delete renderEngine_;
    }

    FpsLimit CoreEngine::fpsLimit() const
    {
        return fpsLimit_;
    }

    bool CoreEngine::displayFps() const
    {
        return displayFPS_;
    }

    int CoreEngine::statusCode() const
    {
        return status_;
    }

    std::string CoreEngine::status() const
    {
        switch(status_)
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
        return renderEngine_;
    }

    std::chrono::milliseconds CoreEngine::frameLockMS() const
    {
        if(fpsLimit_ == FpsLimit::FPS_Unlimited)
            return std::chrono::milliseconds(0);

        return std::chrono::milliseconds(std::chrono::milliseconds(1000 / fpsLimit_));
    }

    void CoreEngine::setRenderEngine(IRenderEngine* _renderEngine)
    {
        renderEngine_ = _renderEngine;
    }

    void CoreEngine::setFrameLimit(FpsLimit _limit)
    {
        fpsLimit_ = _limit;
    }

    void CoreEngine::initialize(IRenderEngine* _renderEngine)
    {
        Log::log("Engine initialization...");

        renderEngine_ = _renderEngine;
        renderEngine_->initialize();

        #ifdef GL_API
            Log::log("API: OpenGL " + renderEngine_->apiVersion());
        #endif

        if(fpsLimit_ == FpsLimit::FPS_Unlimited)
            Log::log("FPS lock: disabled");
        else
            Log::log("FPS lock: " + std::to_string(fpsLimit_) + " fps (~" +
                std::to_string(frameLockMS().count()) + " ms)");

        status_ = StatusCode::Initialized;

        Log::log("Waiting for events...");
    }

    void CoreEngine::run()
    {
        if(status_ != StatusCode::Initialized)
            return;

        status_ = StatusCode::Running;
        renderEngine_->initializePreRenderEffects();
        render();
    }

    void CoreEngine::render()
    {
        if(status_ != StatusCode::Running)
            return;

        renderEngine_->render();
    }

    void CoreEngine::stop()
    {
        if(status_ != StatusCode::Running)
            return;

        status_ = StatusCode::Stopped;
    }

    void CoreEngine::startPollingEvents()
    {
        if(status_ != StatusCode::Running)
            return;

        // Update inputs.
        Mouse::update();
        Keyboard::update();
    }
}
