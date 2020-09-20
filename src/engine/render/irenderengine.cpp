#include "irenderengine.h"

namespace NAGE
{
    IRenderEngine::IRenderEngine()
        : sceneManager_(new SceneManager)
    {

    }

    IRenderEngine::~IRenderEngine()
    {
        delete sceneManager_;
    }

    SceneManager* IRenderEngine::sceneManager()
    {
        return sceneManager_;
    }

    void IRenderEngine::setSceneManager(SceneManager* _manager)
    {
        sceneManager_ = _manager;
    }
}
