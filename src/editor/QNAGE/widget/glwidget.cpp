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
        if(launchWorker_.joinable())
            launchWorker_.join();
    }

    void GLWidget::resizeEvent(QResizeEvent* _event)
    {
        const QSize size = _event->size();

        XWindowAttributes winAttribs;
        XGetWindowAttributes(renderWindow_->display(), renderWindow_->window(), &winAttribs);

        XMoveResizeWindow(
            renderWindow_->display(),
            renderWindow_->window(),
            winAttribs.x, winAttribs.y,
            size.width(),
            size.height()
        );
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
        // TODO: to refactor - should be created when "New Project" button is clicked
        renderWindow_ = new nage::X11OpenGLWindow(800, 600, "NAGE window");
        XReparentWindow(renderWindow_->display(), renderWindow_->window(), this->winId(), 0, 0);
        XMapWindow(renderWindow_->display(), renderWindow_->window());

        launchWorker_ = std::thread([this]() {
            game_->initializeComponents(nage::EngineType::OpenGL, renderWindow_);
            game_->launch();

            emit ready();
        });
        launchWorker_.detach();
    }
}
