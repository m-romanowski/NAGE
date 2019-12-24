#include "glwidget.h"
#include "wrapper/inputwrapper.h"

namespace QNAGE
{
    GLWidget::GLWidget(QWidget* _parent, EngineBridge* _bridge)
        : QOpenGLWidget(_parent),
          bridge(_bridge),
          font(QFont("Helvetica", 10)),
          frameCount(0),
          firstDraw(true),
          gladInitialized(false)
    {
        // Widget settings
        setFocusPolicy(Qt::StrongFocus);

        // Surface format settings.
        surfaceFormat.setVersion(NAGE::GL_CONTEXT_VERSION_MAJOR, NAGE::GL_CONTEXT_VERSION_MINOR);
        surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
        surfaceFormat.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        surfaceFormat.setSwapInterval(0);
        // QSurfaceFormat::setDefaultFormat(surfaceFormat);
        this->setFormat(surfaceFormat);
    }

    GLWidget::~GLWidget()
    {
        delete frameTimer;
        delete bridge;
    }

    void GLWidget::keyPressEvent(QKeyEvent* _event)
    {
        if (_event->isAutoRepeat()) _event->ignore();
        else InputWrapper::registerKeyPress(static_cast<NAGE::KEY>(_event->key()));
    }

    void GLWidget::keyReleaseEvent(QKeyEvent* _event)
    {
        if (_event->isAutoRepeat()) _event->ignore();
        else InputWrapper::registerKeyRelease(static_cast<NAGE::KEY>(_event->key()));
    }

    void GLWidget::mousePressEvent(QMouseEvent* _event)
    {
        InputWrapper::registerMousePress(static_cast<NAGE::MOUSE>(_event->button()));
    }

    void GLWidget::mouseReleaseEvent(QMouseEvent* _event)
    {
        InputWrapper::registerMouseRelease(static_cast<NAGE::MOUSE>(_event->button()));
    }

    void GLWidget::resizeGL(int _width, int _height)
    {
        // When window has been resized => update render area.
        glad_glViewport(0, 0, _width, _height);
        update();
    }

    void GLWidget::initializeGL()
    {
        if(gladLoadGL())
        {
            frameTimer = new QTimer;
            if(!frameTimer->isActive())
            {
                // Connect fps lock timer to updater.
                connect(frameTimer, SIGNAL(timeout()), this, SLOT(update()));
                connect(this, &QOpenGLWidget::frameSwapped, this, &GLWidget::updateGL);
            }

            // FPS lock.
            if(bridge->getFrameLock() == FPS_UNLIMITED)
                frameTimer->start();
            else
                frameTimer->start(bridge->getFrameLockMs());

            // Initialize engine GL.
            if(bridge != nullptr)
                bridge->setup(context());

            // FPS counter time.
            elapsedTime.start();
            gladInitialized = true;

            shader = new NAGE::Shader;
            shader->addShaderFromSourceCode(NAGE::SHADER_TYPE::SHADER_VERTEX,
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "uniform mat4 model;\n"
                "uniform mat4 view;\n"
                "uniform mat4 projection;\n"
                "void main(){\n"
                "gl_Position = projection * view * model * vec4(aPos, 1.0f);}\n\0");
            shader->addShaderFromSourceCode(NAGE::SHADER_TYPE::SHADER_FRAGMENT,
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "void main(){\n"
                "FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);}\n\0");
            shader->link();

            /*std::vector<Vertex> vertices = {
                { Vector3f(0.5f,  0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f) },
                { Vector3f(0.5f, -0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f) },
                { Vector3f(-0.5f, -0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f) },
                { Vector3f(-0.5f,  0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f) }
            };

            std::vector<unsigned int> indices = {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
            };*/

            model = new NAGE::Model("/home/inc/Documents/projects/voidstuff/NAGE/resources/model/cube.obj", shader);
            transform.setTranslation(NAGE::Vector3f(0.0f, 0.0f, -15.0f));
            model->setTransformation(&transform);
        }
        else
        {
            std::error_code code = NAGE::ERROR::GLFW_FAILED_GLAD_INITIALIZATION;
            NAGE::Log::error(code.message());
        }
    }

    void GLWidget::paintGL()
    {
        if(gladInitialized)
        {
            if(firstDraw)
            {
                NAGE::Log::log("Waiting for events...");
                firstDraw = false;
            }

            // Engine render and pool events.
            if(bridge != nullptr)
                bridge->startPollingEvents();

            // Calculate fps.
            frameCount++;
            if(elapsedTime.elapsed() >= 1000 && bridge->displayFps())
            {
                NAGE::Vector3f pos = bridge->getFpsCounterPosition();
                renderText(pos.x(), pos.y(), pos.z(),
                    QString::number(static_cast<int>(frameCount / static_cast<double>(elapsedTime.elapsed() / 1000.0f)))
                        + QString(" fps"));
            }

            model->draw(camera);
        }
    }

    void GLWidget::updateGL()
    {
        InputWrapper::update();

        // TODO: camera movement.
        if(InputWrapper::mouseButtonPressed(NAGE::MOUSE::QEDITOR_MOUSE_RIGHT_BUTTON))
        {
            float transSpeed = 0.1f;
            float rotSpeed   = 0.1f;

            // Handle rotations
            camera.rotate(-rotSpeed * NAGE::Input::mouseDelta().x(), NAGE::Vector3f::up);
            camera.rotate(-rotSpeed * NAGE::Input::mouseDelta().y(), camera.right());

            // Handle translations
            NAGE::Vector3f translation;
            if (InputWrapper::keyPressed(NAGE::KEY::KEY_W)) translation -= camera.forward();
            if (InputWrapper::keyPressed(NAGE::KEY::KEY_S)) translation += camera.forward();
            if (InputWrapper::keyPressed(NAGE::KEY::KEY_A)) translation -= camera.right();
            if (InputWrapper::keyPressed(NAGE::KEY::KEY_D)) translation += camera.right();
            if (InputWrapper::keyPressed(NAGE::KEY::KEY_Q)) translation -= camera.up();
            if (InputWrapper::keyPressed(NAGE::KEY::KEY_E)) translation += camera.up();

            // Set translation vector.
            camera.translate(transSpeed * translation);
        }

        QOpenGLWidget::update();
    }

    void GLWidget::drawFPSCounter()
    {

    }

    void GLWidget::transformPoint(GLfloat out[4], const GLfloat m[16], const GLfloat in[4])
    {
    #define M(row, col)  m[col * 4 + row]
        out[0] =
            M(0, 0) * in[0] + M(0, 1) * in[1] + M(0, 2) * in[2] + M(0, 3) * in[3];
        out[1] =
            M(1, 0) * in[0] + M(1, 1) * in[1] + M(1, 2) * in[2] + M(1, 3) * in[3];
        out[2] =
            M(2, 0) * in[0] + M(2, 1) * in[1] + M(2, 2) * in[2] + M(2, 3) * in[3];
        out[3] =
            M(3, 0) * in[0] + M(3, 1) * in[1] + M(3, 2) * in[2] + M(3, 3) * in[3];
    #undef M
    }

    GLint GLWidget::project(GLfloat objx, GLfloat objy, GLfloat objz,
        const GLfloat model[16], const GLfloat proj[16],
        const GLint viewport[4], GLfloat* winx, GLfloat* winy, GLfloat* winz)
    {
        GLfloat in[4], out[4];

        in[0] = objx;
        in[1] = objy;
        in[2] = objz;
        in[3] = 1.0;
        transformPoint(out, model, in);
        transformPoint(in, proj, out);

        if (in[3] == 0.0f)
            return GL_FALSE;

        in[0] /= in[3];
        in[1] /= in[3];
        in[2] /= in[3];

        *winx = viewport[0] + (1 + in[0]) * viewport[2] / 2;
        *winy = viewport[1] + (1 + in[1]) * viewport[3] / 2;

        *winz = (1 + in[2]) / 2;

        return GL_TRUE;
    }

    void GLWidget::renderText(float _x, float _y, float _z, const QString& _str)
    {
        int height = this->height();

        GLfloat model[4][4], proj[4][4];
        GLint view[4];

        glad_glGetFloatv(GL_MODELVIEW_MATRIX, &model[0][0]);
        glad_glGetFloatv(GL_PROJECTION_MATRIX, &proj[0][0]);
        glad_glGetIntegerv(GL_VIEWPORT, &view[0]);

        GLfloat textPosX = 0, textPosY = 0, textPosZ = 0;

        project(_x, _y, _z,
            &model[0][0], &proj[0][0], &view[0],
            &textPosX, &textPosY, &textPosZ);

        textPosY = height - textPosY; // y is inverted

        QPainter painter(this);
        painter.setPen(QNAGE_YELLOW);
        painter.setFont(font);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        painter.drawText(static_cast<int>(textPosX),
            static_cast<int>(textPosY), _str); // z = pointT4.z + distOverOp / 4
        painter.end();
    }
}
