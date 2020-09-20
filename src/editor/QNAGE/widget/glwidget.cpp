#include <QtConcurrent/QtConcurrentRun>
#include "glwidget.h"

namespace QNAGE
{
    GLWidget::GLWidget(QWidget* _parent)
        : QOpenGLWidget(_parent),
          NAGE::IWindow(QOpenGLWidget::width(), QOpenGLWidget::height()),
          font_(QFont("Helvetica", 10)),
          frameCount_(0),
          gladInitialized_(false),
          sceneNode_(new NAGE::SceneNode)
    {
        // Widget settings
        setFocusPolicy(Qt::StrongFocus);

        // Surface format settings.
        surfaceFormat_.setVersion(NAGE::GL_CONTEXT_VERSION_MAJOR, NAGE::GL_CONTEXT_VERSION_MINOR);
        surfaceFormat_.setProfile(QSurfaceFormat::CoreProfile);
        surfaceFormat_.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        surfaceFormat_.setSwapInterval(0);
        this->setFormat(surfaceFormat_);
    }

    GLWidget::~GLWidget()
    {

    }

    void GLWidget::setGame(NAGE::IGame* _game)
    {
        game_ = _game;
    }

    void GLWidget::keyPressEvent(QKeyEvent* _event)
    {
        if (_event->isAutoRepeat()) _event->ignore();
        else IWindow::keyPressEvent(static_cast<NAGE::Key>(_event->key()));
    }

    void GLWidget::keyReleaseEvent(QKeyEvent* _event)
    {
        if (_event->isAutoRepeat()) _event->ignore();
        else IWindow::keyReleaseEvent(static_cast<NAGE::Key>(_event->key()));
    }

    void GLWidget::mousePressEvent(QMouseEvent* _event)
    {
        IWindow::mousePressEvent(static_cast<NAGE::MouseButton>(_event->button()));
    }

    void GLWidget::mouseReleaseEvent(QMouseEvent* _event)
    {
        IWindow::mouseReleaseEvent(static_cast<NAGE::MouseButton>(_event->button()));
    }

    void GLWidget::wheelEvent(QWheelEvent* _event)
    {
        /*if(_event->angleDelta().y() > 0)
            NAGE::cameraMovementSpeed += QNAGE_WHEEL_STEP;
        else
            NAGE::cameraMovementSpeed -= QNAGE_WHEEL_STEP;

        NAGE::Log::log("Mouse movement speed updated: " + std::to_string(NAGE::cameraMovementSpeed));*/
    }

    void GLWidget::resizeGL(int _width, int _height)
    {
        IWindow::resizeEvent(_width, _height);
        update();
    }

    void GLWidget::sync()
    {
        // Update i.e. inputs, render area.
        std::function<void(void)> updateFunc = std::bind(&GLWidget::update, this);
        updateInterval_->setInterval(updateFunc, game_->engine()->frameLockMS().count());

        std::function<void(void)> renderFPSFunc = std::bind(&GLWidget::renderFPS, this);
        updateInterval_->setInterval(renderFPSFunc, 1000); // Refresh fps text every 1s.
    }

    void GLWidget::initializeGL()
    {
        if(initialized())
        {
            gladInitialized_ = true;

            // Initialize update timers.
            sync();

            // Initialize engine components.
            game_->initializeComponents(NAGE::EngineType::OpenGL, this);

            sceneNode_->addToScene(&camera_);
            game_->sceneManager()->addChild("editor", sceneNode_);

            // Initialize game scene and run engine.
            game_->initializeScene();
            game_->launch();
        }
    }

    void GLWidget::paintGL()
    {
        if(gladInitialized_)
        {
            // Editor keyboard options.
            if(NAGE::Keyboard::keyPressed(NAGE::Key::KEY_F)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            if(NAGE::Keyboard::keyReleased(NAGE::Key::KEY_F)) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // Start rendering scene(s).
            game_->engine()->render();
        }
    }

    void GLWidget::update()
    {
        // Update FPS
        frameCount_++;

        // Engine pool event
        game_->engine()->startPollingEvents();

        if(NAGE::Mouse::mouseButtonPressed(NAGE::MouseButton::QEDITOR_MOUSE_RIGHT_BUTTON))
        {
            // Handle camera rotations.
            camera_.rotate(-NAGE::cameraSensitivity * NAGE::Mouse::mouseDelta().x(),
                NAGE::Vector3f::up);

            //mCamera.rotate(-NAGE::cameraSensitivity * NAGE::Mouse::mouseDelta().y(),
            //    mCamera.right());

            // Handle camera translations.
            NAGE::Vector3f translation;
            if(NAGE::Keyboard::keyPressed(NAGE::Key::KEY_W)) translation -= camera_.forward();
            if(NAGE::Keyboard::keyPressed(NAGE::Key::KEY_S)) translation += camera_.forward();
            if(NAGE::Keyboard::keyPressed(NAGE::Key::KEY_A)) translation -= camera_.right();
            if(NAGE::Keyboard::keyPressed(NAGE::Key::KEY_D)) translation += camera_.right();
            if(NAGE::Keyboard::keyPressed(NAGE::Key::KEY_Q)) translation -= camera_.up();
            if(NAGE::Keyboard::keyPressed(NAGE::Key::KEY_E)) translation += camera_.up();

            /* Movement must be independent of FPS (frames per second),
             * We need compute delta time for each update and multiplicate
             * with translation vector.
             */
            float delta = static_cast<float>(IWindow::deltaMs());
            camera_.translate(NAGE::cameraMovementSpeed * delta * translation);
        }

        // Update QT OpenGL context.
        QOpenGLWidget::update();
    }

    void GLWidget::renderFPS()
    {
        frameCount_ = 0;
    }
}
