#ifndef QNAGE_WIDGET_GLWIDGET_H_
#define QNAGE_WIDGET_GLWIDGET_H_

#include "wrapper/enginebridge.h"
#include "engine/render/model/model.h"

#include <QCoreApplication>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QColor>
#include <QSurfaceFormat>

#include <chrono>
#include <iostream>

#define QNAGE_YELLOW Qt::yellow
#define QNAGEL_RED Qt::red

namespace QNAGE
{
    class GLWidget : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        GLWidget(QWidget* _parent = nullptr, EngineBridge* _bridge = nullptr);
        ~GLWidget() override;

        // Getters
        inline EngineBridge* getBridge() const { return bridge; }

        // Setters
        inline void setBridge(EngineBridge* _bridge) { bridge = _bridge; }

        // Public methods
        void renderText(float _x, float _y, float _z, const QString& _str);

    protected:
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _width, int _height) override;
        void keyPressEvent(QKeyEvent* _event) override;
        void keyReleaseEvent(QKeyEvent* _event) override;
        void mousePressEvent(QMouseEvent* _event) override;
        void mouseReleaseEvent(QMouseEvent* _event) override;

    protected slots:
        void updateGL();

    private:
        void drawFPSCounter();
        void transformPoint(GLfloat out[4], const GLfloat m[16], const GLfloat in[4]);
        GLint project(GLfloat objx, GLfloat objy, GLfloat objz,
            const GLfloat model[16], const GLfloat proj[16],
            const GLint viewport[4], GLfloat* winx, GLfloat* winy, GLfloat* winz);

        // Core engine.
        EngineBridge* bridge;

        // GLWidget settings
        QSurfaceFormat surfaceFormat;

        // FPS timers.
        QTimer* frameTimer;
        QTime elapsedTime;

        // FPS counter settings
        QFont font;
        int frameCount;
        bool firstDraw;
        bool gladInitialized;

        // TMP : remove that
        NAGE::Shader* shader;
        NAGE::Model* model;
        NAGE::Transform transform;
        NAGE::Camera camera;
    };
}

#endif // QNAGE_WIDGET_GLWIDGET_H_
