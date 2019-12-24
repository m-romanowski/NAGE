#ifndef QNAGE_WRAPPER_ENGINEBRIDGE_H_
#define QNAGE_WRAPPER_ENGINEBRIDGE_H_

#include "engine/components/types.h"
#include "engine/core/igame.h"
#include "engine/core/coreengine.h"
#include "engine/render/irenderengine.h"

#include <QOpenGLContext>

/* Bridge Engine <-> Editor.
 *
 * We need create a bridge between engine and world editor. World creator
 * uses QT interface for draw area. This bridge is used only for WORLD EDITOR. If you compile
 * release game it will be used GLFW interface.
 *
 * Engine - GLFW context
 * Editor - QOpenGLContext
 */
namespace QNAGE
{
    class EngineBridge : public NAGE::CoreEngine
    {
    public:
        EngineBridge(NAGE::IRenderEngine* _renderEngine, NAGE::IGame* _game, NAGE::FpsLimit _fpsLimit = NAGE::FpsLimit::FPS_Unlimited);
        ~EngineBridge();

        // Getters
        inline QOpenGLContext* getGLContext() const { return context; }

        // Setters
        inline void setGLContext(QOpenGLContext* _context) { context = _context; }

        void setup(QOpenGLContext* _context);
        void startPollingEvents();
    private:
        QOpenGLContext* context;
    };
}

#endif // QNAGE_WRAPPER_ENGINEBRIDGE_H_
