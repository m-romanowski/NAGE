#ifndef QNAGE_LOG_LOGWIDGET_H_
#define QNAGE_LOG_LOGWIDGET_H_

#include "messagehandler.h"
#include "threadlogstream.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QVariant>
#include <QPlainTextEdit>
#include <QString>
#include <QScrollBar>

#include <iostream>

namespace QNAGE
{
    class LogWidget : public QWidget
    {
        Q_OBJECT

    public:
        LogWidget(QWidget* _parent = nullptr);
        virtual ~LogWidget();

        // QMessage - redirect to IO (iostream library).
        static void QMessageOutput(QtMsgType _type, const QMessageLogContext& _context, const QString& _msg);

    private slots:
        void onClearButtonClicked();
        void onDebugIOChange();

    private:
        void setupUi();

        // IO output handler (e.g. std::cout from iostream library)
        MessageHandler* msgHandler;
        ThreadLogStream* logStream;

        // Ui
        QVBoxLayout* mainLayout;
        QGridLayout* optLayout;

        QPlainTextEdit* debugIO;
        QPushButton* clearButton;
    };
}

#endif // QNAGE_LOG_LOGWIDGET_H_
