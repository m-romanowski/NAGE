#include "enginebridge.h"

namespace QNAGE
{
    EngineBridge::EngineBridge(NAGE::IRenderEngine* _renderEngine, NAGE::IGame* _game, int _fpsLock)
        : NAGE::Engine(_renderEngine, _game, _fpsLock)
    {

    }

    EngineBridge::~EngineBridge()
    {

    }

    /* Setup OpenGL context (QOpenGLContext), initialize rendering engine and debug logs.
     */
    void EngineBridge::setup(QOpenGLContext* _context)
    {
        if(!game->initialized())
        {
            std::error_code code = NAGE::ERROR::ENGINE_FAILED_GAME_INITIALIZATION;
            NAGE::Log::critical(code.message());
        }

        context = _context;
        renderEngine->initialize();

        setupLog();
    }

    /* Start render scene.
     */
    void EngineBridge::startPollingEvents()
    {
        renderEngine->render(game->getSceneManager());
    }
}
