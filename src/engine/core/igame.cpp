#include "igame.h"

namespace NAGE
{
    IGame::IGame(FpsLimit _limit)
    {
        mCoreEngine = new CoreEngine;
        mCoreEngine->setFrameLimit(_limit);
    }

    IGame::~IGame()
    {

    }

    CoreEngine* IGame::engine()
    {
        return mCoreEngine;
    }

    SceneManager* IGame::sceneManager()
    {
        return mCoreEngine->renderEngine()->sceneManager();
    }

    void IGame::setEngine(CoreEngine* _engine)
    {
        mCoreEngine = _engine;
    }

    void IGame::initializeComponents(EngineType _type, IWindow* _window)
    {
        if(_type == EngineType::OpenGL)
            mCoreEngine->initialize(new GLRenderEngine(_window));
    }

    void IGame::launch()
    {
        mCoreEngine->run();
    }
}
