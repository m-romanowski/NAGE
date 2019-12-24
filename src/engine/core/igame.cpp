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

    void IGame::initializeComponents(EngineType _type)
    {
        if(_type == EngineType::OpenGL)
            mCoreEngine->initialize(new GLRenderEngine);
    }

    void IGame::launch()
    {
        mCoreEngine->run();
    }
}
