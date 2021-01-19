#include "engine/core/igame.h"
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
        // Stop engine and all sub-components.
        stop();

        delete renderEngine_;
        delete game_;
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

    void CoreEngine::initialize(IRenderEngine* _renderEngine, IGame* _game)
    {
        Log::log("Engine initialization...");

        renderEngine_ = _renderEngine;
        game_ = _game;

        if(fpsLimit_ == FpsLimit::FPS_Unlimited)
            Log::log("FPS lock: disabled");
        else
            Log::log("FPS lock: " + std::to_string(fpsLimit_) + " fps (~" + std::to_string(frameLockMS().count()) + " ms)");

        status_.store(StatusCode::Initialized);
    }

    void CoreEngine::run()
    {
        if(status_.load() != StatusCode::Initialized)
            return;

        status_.store(StatusCode::Running);
        mainWorker_ = std::thread([this]() {
            renderEngine_->initialize();
            renderEngine_->initializePreRenderEffects();
            game_->initializeScene();

            Log::log("Waiting for events...");

            render();
        });
        mainWorker_.detach();
    }

    void CoreEngine::stop()
    {
        if(!isRunning())
            return;

        if(mainWorker_.joinable())
            mainWorker_.join();

        status_.store(StatusCode::Stopped);
    }

    bool CoreEngine::isRunning()
    {
        return status_.load() == StatusCode::Running;
    }

    void CoreEngine::render()
    {
        if(!isRunning())
            return;

        while(isRunning())
        {
            pollEvents();
            renderEngine_->render();

            std::this_thread::sleep_for(frameLockMS());
        }
    }

    void CoreEngine::pollEvents()
    {
        if(!isRunning())
            return;

        Mouse::update();
        Keyboard::update();

        // Run pre-render tasks.
        renderEngine_->preRender();
        game_->ioEventsSupplier();
    }
}
