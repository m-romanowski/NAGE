#ifndef QNAGE_WINDOW_FRAMELESSWINDOW_H_
#define QNAGE_WINDOW_FRAMELESSWINDOW_H_

#include "ui/custombutton.h"

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QIcon>

namespace QNAGE
{
    const unsigned int FRAMELESSWINDOW_WITHOUT_BUTTONS = 0;
    const unsigned int FRAMELESSWINDOW_ALL_BUTTONS = 1;
    const unsigned int FRAMELESSWINDOW_EXIT_BUTTON = 2;
    const unsigned int FRAMELESSWINDOW_EXIT_MINIMIZE_BUTTONS = 3;

    class FramelessWindow : public QWidget
    {
        Q_OBJECT

    public:
        FramelessWindow(QWidget* _parent = nullptr, unsigned int _type = 1);
        virtual ~FramelessWindow();

        // Getters
        inline unsigned int getWindowType() const { return type; }

        // Setters
        inline void setMainLayout(QLayout* _layout) { mainLayout = _layout; init(); }

    protected slots:
        virtual void mouseMoveEvent(QMouseEvent* _event);
        virtual void mousePressEvent(QMouseEvent* _event);
        virtual void mouseReleaseEvent(QMouseEvent* _event);
        virtual void mouseDoubleClickEvent(QMouseEvent* _event);
        virtual void onExitButtonClicked();
        virtual void onMaximizeButtonClicked();
        virtual void onMinimizeButtonClicked();

    protected:
        // Main window components.
        QLayout* mainLayout;
        QGridLayout* topLayout;
        QWidget* windowTitleWidget;

    private:
        void init();

        unsigned int type;
        bool isMoving;
        QPoint lastMousePosition;

        // Ui
        QWidget* topLayoutWidget;

        CustomButton* exitButton;
        CustomButton* minimizeButton;
        CustomButton* maximizeButton;
    };
}

#endif // QNAGE_WINDOW_FRAMELESSWINDOW_H_
