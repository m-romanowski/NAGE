#ifndef QNAGE_DIALOG_PROJECTDIALOG_H_
#define QNAGE_DIALOG_PROJECTDIALOG_H_

#include "window/framelesswindow.h"
#include "ui/tabwidget.h"
#include "dialog.h"

#include <QVBoxLayout>
#include <QSizeGrip>
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QSpacerItem>

namespace QNAGE
{
    class ProjectDialog : public FramelessWindow, public Dialog
    {
        Q_OBJECT

    public:
        ProjectDialog(QWidget* _parent = nullptr);
        virtual ~ProjectDialog() override;

    private:
        virtual void setupUi() override;

        // Ui
        QVBoxLayout* layout;
        TabWidget* tabWidget;

        // Create a new project
        QWidget* createProjectWidget;
        QVBoxLayout* createProjectLayout;
        QGridLayout* projectWidgetsLayout;
        QLabel* projectMainLabel;
        QLabel* projectMainDescription;
        QLineEdit* projectNameInput;
        QLineEdit* projectDirInput;
        QPushButton* browseButton;
        QPushButton* createButton;
        QPushButton* cancelButton;
    };
}

#endif // QNAGE_DIALOG_PROJECTDIALOG_H_
