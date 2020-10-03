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

namespace mr::qnage
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
        QVBoxLayout* layout_;
        TabWidget* tabWidget_;

        // Create a new project
        QWidget* createProjectWidget_;
        QVBoxLayout* createProjectLayout_;
        QGridLayout* projectWidgetsLayout_;
        QLabel* projectMainLabel_;
        QLabel* projectMainDescription_;
        QLineEdit* projectNameInput_;
        QLineEdit* projectDirInput_;
        QPushButton* browseButton_;
        QPushButton* createButton_;
        QPushButton* cancelButton_;
    };
}

#endif // QNAGE_DIALOG_PROJECTDIALOG_H_
