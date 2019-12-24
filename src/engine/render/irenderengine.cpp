#include "irenderengine.h"

namespace NAGE
{
    IRenderEngine::IRenderEngine()
        : mSceneManager(new SceneManager)
    {

    }

    IRenderEngine::~IRenderEngine()
    {
        delete mSceneManager;
    }

    SceneManager* IRenderEngine::sceneManager()
    {
        return mSceneManager;
    }

    void IRenderEngine::setSceneManager(SceneManager* _manager)
    {
        mSceneManager = _manager;
    }
}
