#ifndef QNAGE_WIDGET_WELCOMEWIDGET_H_
#define QNAGE_WIDGET_WELCOMEWIDGET_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QSizePolicy>

namespace QNAGE
{
    class WelcomeWidget : public QWidget
    {
    public:
        WelcomeWidget(QWidget* _parent = nullptr);
        ~WelcomeWidget();

        // Getters
        QPushButton* getCreateButton() const { return createProjectButton; }

    private:
        void setupUi();

        // Ui
        QVBoxLayout* mainLayout;
        QGridLayout* buttonsLayout;
        QLabel* appName;
        QLabel* sessionLabel;
        QLabel* sessionDir;
        QSpacerItem* verticalSpacer1;
        QSpacerItem* verticalSpacer2;
        QSpacerItem* horizontalSpacer;
        QPushButton* createProjectButton;
        QPushButton* openProjectButton;
    };
}

#endif // QNAGE_WIDGET_WELCOMEWIDGET_H_
