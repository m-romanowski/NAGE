#ifndef QNAGE_WIDGET_GLWIDGET_H_
#define QNAGE_WIDGET_GLWIDGET_H_

#include "engine/core/igame.h"
#include "engine/render/projection.h"
#include "engine/io/iwindow.h"
#include "engine/components/camera/camera.h"

#include <QCoreApplication>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QColor>
#include <QSurfaceFormat>
#include <QMouseEvent>
#include <QWheelEvent>

#include <chrono>
#include <iostream>

#define QNAGE_YELLOW Qt::yellow
#define QNAGEL_RED Qt::red

//#define QNAGE_WHEEL_STEP 0.01

namespace QNAGE
{
    class GLWidget : public QOpenGLWidget, public NAGE::IWindow
    {
        Q_OBJECT

    public:
        GLWidget(QWidget* _parent = nullptr);
        ~GLWidget() override;

        // Setters
        void setGame(NAGE::IGame* _game);

        // Public methods
        void renderText(float _x, float _y, float _z, const QString& _str);
        void renderText(const NAGE::Vector3f& _position, const QString& _str);

    protected:
        void sync() override;
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _width, int _height) override;
        void keyPressEvent(QKeyEvent* _event) override;
        void keyReleaseEvent(QKeyEvent* _event) override;
        void mousePressEvent(QMouseEvent* _event) override;
        void mouseReleaseEvent(QMouseEvent* _event) override;
        void wheelEvent(QWheelEvent* _event) override;

    protected slots:
        void update();

    private:
        void renderFPS();
        void transformPoint(GLfloat out[4], const GLfloat m[16], const GLfloat in[4]);
        GLint project(GLfloat objx, GLfloat objy, GLfloat objz,
            const GLfloat model[16], const GLfloat proj[16],
            const GLint viewport[4], GLfloat* winx, GLfloat* winy, GLfloat* winz);

        // Game
        NAGE::IGame* mGame;

        // GLWidget settings
        QSurfaceFormat surfaceFormat;

        // FPS counter
        QFont font;
        int frameCount;
        long lastFrame;

        // GLAD
        bool gladInitialized;

        // Editor camera
        NAGE::Camera mCamera;
        NAGE::SceneNode* mSceneNode;
    };
}

#endif // QNAGE_WIDGET_GLWIDGET_H_
