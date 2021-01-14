#include "qnage.h"

namespace mr::qnage
{
    QNAGE::~QNAGE()
    {
        delete mainWindow_;
    }

    void QNAGE::setup(nage::IGame* _game)
    {
        this->mainWindow_ = new MainWindow;

        // Bind NAGE window to render widget.
        RenderWindow* renderWindow = new RenderWindow(mainWindow_);
        renderWindow->setupGLWidget(_game);

        // Add gl window to main window and show.
        this->mainWindow_->addWindow(renderWindow);

        // Show window
        this->mainWindow_->show();
    }
}
