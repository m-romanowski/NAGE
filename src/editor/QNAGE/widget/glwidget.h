#ifndef QNAGE_WIDGET_GLWIDGET_H_
#define QNAGE_WIDGET_GLWIDGET_H_

#include "engine/core/igame.h"

#include <QWidget>
#include <QResizeEvent>

#include <thread>

namespace mr::nage
{
    class X11OpenGLWindow;
}

namespace mr::qnage
{

    class GLWidget
        : public QWidget
    {
        Q_OBJECT

    public:
        GLWidget(QWidget* _parent = nullptr);
        ~GLWidget();

        void initialize(nage::IGame* _game);
        void startRendering();

    protected:
        void resizeEvent(QResizeEvent* _event);

    private:
        nage::IGame* game_;
        nage::X11OpenGLWindow* renderWindow_;
        std::thread renderWorker_;
    };
}

#endif // QNAGE_WIDGET_GLWIDGET_H_
