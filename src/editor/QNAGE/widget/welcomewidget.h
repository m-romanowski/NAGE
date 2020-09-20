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
        QPushButton* getCreateButton() const { return createProjectButton_; }

    private:
        void setupUi();

        // Ui
        QVBoxLayout* mainLayout_;
        QGridLayout* buttonsLayout_;
        QLabel* appName_;
        QLabel* sessionLabel_;
        QLabel* sessionDir_;
        QSpacerItem* verticalSpacer1_;
        QSpacerItem* verticalSpacer2_;
        QSpacerItem* horizontalSpacer_;
        QPushButton* createProjectButton_;
        QPushButton* openProjectButton_;
    };
}

#endif // QNAGE_WIDGET_WELCOMEWIDGET_H_
