#include "igame.h"

namespace mr::nage
{
    IGame::IGame(FpsLimit _limit)
    {
        coreEngine_ = new CoreEngine;
        coreEngine_->setFrameLimit(_limit);
    }

    IGame::~IGame()
    {

    }

    CoreEngine* IGame::engine()
    {
        return coreEngine_;
    }

    SceneManager* IGame::sceneManager()
    {
        return coreEngine_->renderEngine()->sceneManager();
    }

    void IGame::setEngine(CoreEngine* _engine)
    {
        coreEngine_ = _engine;
    }

    void IGame::initializeComponents(EngineType _type, IWindow* _window)
    {
        if(_type == EngineType::OpenGL)
            coreEngine_->initialize(new GLRenderEngine(_window), this);
    }

    void IGame::launch()
    {
        coreEngine_->run();
    }
}
