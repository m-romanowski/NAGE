#include <QtConcurrent/QtConcurrentRun>
#include "glwidget.h"
#include "engine/io/x11openglwindow.h"

namespace mr::qnage
{
    GLWidget::GLWidget(QWidget* _parent)
        : QWidget(_parent),
          game_(nullptr)
    {
        // Widget settings
        setFocusPolicy(Qt::StrongFocus);
    }

    GLWidget::~GLWidget()
    {
        if(renderWorker_.joinable())
            renderWorker_.join();
    }

    void GLWidget::resizeEvent(QResizeEvent* _event)
    {
        // TODO: resize x11 window wth on `GLWidget` resize event.
        XResizeRequestEvent resizeEvent;
        resizeEvent.width = _event->size().width();
        resizeEvent.height = _event->size().height();
        resizeEvent.display = renderWindow_->display();
        resizeEvent.window = renderWindow_->window();

        XSendEvent(renderWindow_->display(), renderWindow_->window(), False, ResizeRedirectMask, (XEvent *)&resizeEvent);
    }

    nage::IGame* GLWidget::game()
    {
        return game_;
    }

    void GLWidget::initialize(nage::IGame* _game)
    {
        game_ = _game;
    }

    void GLWidget::startRendering()
    {
        renderWindow_ = new nage::X11OpenGLWindow(800, 600, "NAGE window");
        XReparentWindow(renderWindow_->display(), renderWindow_->window(), this->winId(), 0, 0);
        XMapWindow(renderWindow_->display(), renderWindow_->window());

        renderWorker_ = std::thread([this]() {
            game_->initializeComponents(nage::EngineType::OpenGL, renderWindow_);
            game_->initializeScene();

            emit ready();

            game_->launch();
        });
        renderWorker_.detach();
    }
}
